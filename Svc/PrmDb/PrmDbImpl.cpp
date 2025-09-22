/*
 * PrmDbImpl.cpp
 *
 *  Created on: March 9, 2015
 *      Author: Timothy Canham
 */

#include <Fw/Types/Assert.hpp>
#include <Svc/PrmDb/PrmDbImpl.hpp>

#include <Os/File.hpp>

#include <cstdio>
#include <cstring>

static_assert(std::numeric_limits<FwSizeType>::max() >= PRMDB_NUM_DB_ENTRIES,
              "PRMDB_NUM_DB_ENTRIES must fit within range of FwSizeType");

namespace Svc {

// anonymous namespace for buffer declaration
namespace {
class WorkingBuffer : public Fw::SerializeBufferBase {
  public:
    FwSizeType getBuffCapacity() const { return sizeof(m_buff); }

    U8* getBuffAddr() { return m_buff; }

    const U8* getBuffAddr() const { return m_buff; }

  private:
    // Set to max of parameter buffer + id
    U8 m_buff[FW_PARAM_BUFFER_MAX_SIZE + sizeof(FwPrmIdType)];
};
}  // namespace

PrmDbImpl::PrmDbImpl(const char* name) : PrmDbComponentBase(name) {
    this->clearDb(PrmDbType::DB_PRIME);
    this->clearDb(PrmDbType::DB_BACKUP);
}

void PrmDbImpl::configure(const char* file) {
    FW_ASSERT(file != nullptr);
    this->m_fileName = file;
}

void PrmDbImpl::clearDb(PrmDbType prmDbType) {
    t_dbStruct* db;
    getDbPtr(prmDbType, &db);
    for (FwSizeType entry = 0; entry < PRMDB_NUM_DB_ENTRIES; entry++) {
        db[entry].used = false;
        db[entry].id = 0;
    }
}

// If ports are no longer guarded, these accesses need to be protected from each other
// If there are a lot of accesses, perhaps an interrupt lock could be used instead of guarded ports

Fw::ParamValid PrmDbImpl::getPrm_handler(FwIndexType portNum, FwPrmIdType id, Fw::ParamBuffer& val) {
    // search for entry
    Fw::ParamValid stat = Fw::ParamValid::INVALID;

    for (FwSizeType entry = 0; entry < PRMDB_NUM_DB_ENTRIES; entry++) {
        if (this->m_dbPrime[entry].used) {
            if (this->m_dbPrime[entry].id == id) {
                val = this->m_dbPrime[entry].val;
                stat = Fw::ParamValid::VALID;
                break;
            }
        }
    }

    // if unable to find parameter, send error message
    if (Fw::ParamValid::INVALID == stat.e) {
        this->log_WARNING_LO_PrmIdNotFound(id);
    }

    return stat;
}

PrmDbImpl::paramUpdateType PrmDbImpl::updateAddPrm(FwPrmIdType id,
                                                   Fw::ParamBuffer& val,
                                                   PrmDbType prmDbType,
                                                   FwSizeType* index) {
    paramUpdateType updateStatus = NO_SLOTS;

    t_dbStruct* db;
    getDbPtr(prmDbType, &db);

    this->lock();
    // search for existing entry

    bool existingEntry = false;

    for (FwSizeType entry = 0; entry < PRMDB_NUM_DB_ENTRIES; entry++) {
        if ((db[entry].used) && (id == db[entry].id)) {
            db[entry].val = val;
            existingEntry = true;
            updateStatus = PARAM_UPDATED;
            if (index != nullptr) {
                *index = entry;
            }
            break;
        }
    }

    // if there is no existing entry, add one
    if (!existingEntry) {
        for (FwSizeType entry = 0; entry < PRMDB_NUM_DB_ENTRIES; entry++) {
            if (!(db[entry].used)) {
                db[entry].val = val;
                db[entry].id = id;
                db[entry].used = true;
                updateStatus = PARAM_ADDED;
                if (index != nullptr) {
                    *index = entry;
                }
                break;
            }
        }
    }

    this->unLock();
    return updateStatus;
}

void PrmDbImpl::setPrm_handler(FwIndexType portNum, FwPrmIdType id, Fw::ParamBuffer& val) {
    FwSizeType index;  // Which index was used for this parameter

    // Update in the backup DB first
    paramUpdateType update_status = updateAddPrm(id, val, PrmDbType::DB_BACKUP, &index);

    // Issue relevant EVR
    // Copy to primary DB if added or updated
    if (update_status == PARAM_UPDATED) {
        dbCopySingle(PrmDbType::DB_PRIME, PrmDbType::DB_BACKUP, index);
        this->log_ACTIVITY_HI_PrmIdUpdated(id);
    } else if (update_status == NO_SLOTS) {
        this->log_FATAL_PrmDbFull(id);
    } else {
        dbCopySingle(PrmDbType::DB_PRIME, PrmDbType::DB_BACKUP, index);
        this->log_ACTIVITY_HI_PrmIdAdded(id);
    }
}

void PrmDbImpl::PRM_SAVE_FILE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    PrmDbType dbType = PrmDbType::DB_PRIME;  // default, could be changed later to be an argument

    FW_ASSERT(dbType == PrmDbType::DB_PRIME or dbType == PrmDbType::DB_BACKUP);
    FW_ASSERT(this->m_fileName.length() > 0);

    t_dbStruct* db;
    if (dbType == PrmDbType::DB_PRIME) {
        db = this->m_dbPrime;
    } else if (dbType == PrmDbType::DB_BACKUP) {
        db = this->m_dbBackup;
    } else {
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::VALIDATION_ERROR);
        return;
    }

    Os::File paramFile;
    WorkingBuffer buff;

    Os::File::Status stat = paramFile.open(this->m_fileName.toChar(), Os::File::OPEN_WRITE);
    if (stat != Os::File::OP_OK) {
        this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::OPEN, 0, stat);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    this->lock();

    // Traverse the parameter list, saving each entry

    U32 numRecords = 0;

    for (FwSizeType entry = 0; entry < PRMDB_NUM_DB_ENTRIES; entry++) {
        if (db[entry].used) {
            // write delimiter
            static const U8 delim = PRMDB_ENTRY_DELIMITER;
            FwSizeType writeSize = static_cast<FwSizeType>(sizeof(delim));
            stat = paramFile.write(&delim, writeSize, Os::File::WaitType::WAIT);
            if (stat != Os::File::OP_OK) {
                this->unLock();
                this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::DELIMITER, static_cast<I32>(numRecords), stat);
                this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
                return;
            }
            if (writeSize != sizeof(delim)) {
                this->unLock();
                this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::DELIMITER_SIZE, static_cast<I32>(numRecords),
                                                       static_cast<I32>(writeSize));
                this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
                return;
            }
            // serialize record size = id field + data
            U32 recordSize = static_cast<U32>(sizeof(FwPrmIdType) + db[entry].val.getBuffLength());

            // reset buffer
            buff.resetSer();
            Fw::SerializeStatus serStat = buff.serializeFrom(recordSize);
            // should always work
            FW_ASSERT(Fw::FW_SERIALIZE_OK == serStat, static_cast<FwAssertArgType>(serStat));

            // write record size
            writeSize = static_cast<FwSizeType>(buff.getBuffLength());
            stat = paramFile.write(buff.getBuffAddr(), writeSize, Os::File::WaitType::WAIT);
            if (stat != Os::File::OP_OK) {
                this->unLock();
                this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::RECORD_SIZE, static_cast<I32>(numRecords), stat);
                this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
                return;
            }
            if (writeSize != sizeof(recordSize)) {
                this->unLock();
                this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::RECORD_SIZE_SIZE, static_cast<I32>(numRecords),
                                                       static_cast<I32>(writeSize));
                this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
                return;
            }

            // reset buffer
            buff.resetSer();

            // serialize parameter id

            serStat = buff.serializeFrom(this->m_db[entry].id);
            // should always work
            FW_ASSERT(Fw::FW_SERIALIZE_OK == serStat, static_cast<FwAssertArgType>(serStat));

            // write parameter ID
            writeSize = static_cast<FwSizeType>(buff.getBuffLength());
            stat = paramFile.write(buff.getBuffAddr(), writeSize, Os::File::WaitType::WAIT);
            if (stat != Os::File::OP_OK) {
                this->unLock();
                this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::PARAMETER_ID, static_cast<I32>(numRecords), stat);
                this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
                return;
            }
            if (writeSize != static_cast<FwSizeType>(buff.getBuffLength())) {
                this->unLock();
                this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::PARAMETER_ID_SIZE, static_cast<I32>(numRecords),
                                                       static_cast<I32>(writeSize));
                this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
                return;
            }

            // write serialized parameter value

            writeSize = static_cast<FwSizeType>(db[entry].val.getBuffLength());
            stat = paramFile.write(db[entry].val.getBuffAddr(), writeSize, Os::File::WaitType::WAIT);
            if (stat != Os::File::OP_OK) {
                this->unLock();
                this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::PARAMETER_VALUE, static_cast<I32>(numRecords),
                                                       stat);
                this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
                return;
            }
            if (writeSize != static_cast<FwSizeType>(db[entry].val.getBuffLength())) {
                this->unLock();
                this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::PARAMETER_VALUE_SIZE,
                                                       static_cast<I32>(numRecords), static_cast<I32>(writeSize));
                this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
                return;
            }
            numRecords++;
        }  // end if record in use
    }  // end for each record

    this->unLock();
    this->log_ACTIVITY_HI_PrmFileSaveComplete(numRecords);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void PrmDbImpl::PRM_SET_FILE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdStringArg& fileName) {
    Fw::CmdResponse retVal = Fw::CmdResponse::EXECUTION_ERROR;

    // Update Prime
    bool prime_ok = PrmDbImpl::readParamFileImpl(fileName, PrmDbType::DB_PRIME);

    if (prime_ok) {
        // Update Prime
        bool backup_ok = PrmDbImpl::readParamFileImpl(fileName, PrmDbType::DB_BACKUP);
        if (backup_ok) {
            retVal = Fw::CmdResponse::OK;
        }
    } else {
        // Revert Prime using Backup
        dbCopy(PrmDbType::DB_PRIME, PrmDbType::DB_BACKUP);
    }

    // Prime/backup should be the same after
    FW_ASSERT(static_cast<FwAssertArgType>(dbEqual()));

    this->cmdResponse_out(opCode, cmdSeq, retVal);
}

PrmDbImpl::~PrmDbImpl() {}

void PrmDbImpl::readParamFile() {
    // Assumed to run at initialization time

    // Clear databases
    this->clearDb(PrmDbType::DB_PRIME);
    this->clearDb(PrmDbType::DB_BACKUP);

    // Read parameter file to prime and backup
    bool prime_ok = readParamFileImpl(this->m_fileName, PrmDbType::DB_PRIME);
    if (prime_ok) {
        dbCopy(PrmDbType::DB_BACKUP, PrmDbType::DB_PRIME);
        FW_ASSERT(static_cast<FwAssertArgType>(dbEqual()));
    }
}

bool PrmDbImpl::readParamFileImpl(const Fw::StringBase& fileName, PrmDbType dbType) {
    FW_ASSERT(fileName.length() > 0);

    t_dbStruct* db;
    getDbPtr(dbType, &db);
    Fw::String dbString = getDbString(dbType);

    // load file. FIXME: Put more robust file checking, such as a CRC.
    Os::File paramFile;

    Os::File::Status stat = paramFile.open(fileName.toChar(), Os::File::OPEN_READ);
    if (stat != Os::File::OP_OK) {
        this->log_WARNING_HI_PrmFileReadError(PrmReadError::OPEN, 0, stat);
        return false;
    }

    WorkingBuffer buff;

    U32 recordNumTotal = 0;
    U32 recordNumAdded = 0;
    U32 recordNumUpdated = 0;

    for (FwSizeType entry = 0; entry < PRMDB_NUM_DB_ENTRIES; entry++) {
        U8 delimiter;
        FwSizeType readSize = static_cast<FwSizeType>(sizeof(delimiter));

        // read delimiter
        Os::File::Status fStat = paramFile.read(&delimiter, readSize, Os::File::WaitType::WAIT);

        // check for end of file (read size 0)
        if (0 == readSize) {
            break;
        }

        if (fStat != Os::File::OP_OK) {
            this->log_WARNING_HI_PrmFileReadError(PrmReadError::DELIMITER, static_cast<I32>(recordNumTotal), fStat);
            return false;
        }

        if (sizeof(delimiter) != readSize) {
            this->log_WARNING_HI_PrmFileReadError(PrmReadError::DELIMITER_SIZE, static_cast<I32>(recordNumTotal),
                                                  static_cast<I32>(readSize));
            return false;
        }

        if (PRMDB_ENTRY_DELIMITER != delimiter) {
            this->log_WARNING_HI_PrmFileReadError(PrmReadError::DELIMITER_VALUE, static_cast<I32>(recordNumTotal),
                                                  delimiter);
            return false;
        }

        U32 recordSize = 0;

        // read record size
        readSize = sizeof(recordSize);

        fStat = paramFile.read(buff.getBuffAddr(), readSize, Os::File::WaitType::WAIT);
        if (fStat != Os::File::OP_OK) {
            this->log_WARNING_HI_PrmFileReadError(PrmReadError::RECORD_SIZE, static_cast<I32>(recordNumTotal), fStat);
            return false;
        }
        if (sizeof(recordSize) != readSize) {
            this->log_WARNING_HI_PrmFileReadError(PrmReadError::RECORD_SIZE_SIZE, static_cast<I32>(recordNumTotal),
                                                  static_cast<I32>(readSize));
            return false;
        }
        // set serialized size to read size
        Fw::SerializeStatus desStat = buff.setBuffLen(static_cast<Fw::Serializable::SizeType>(readSize));
        // should never fail
        FW_ASSERT(Fw::FW_SERIALIZE_OK == desStat, static_cast<FwAssertArgType>(desStat));
        // reset deserialization
        buff.resetDeser();
        // deserialize, since record size is serialized in file
        desStat = buff.deserializeTo(recordSize);
        FW_ASSERT(Fw::FW_SERIALIZE_OK == desStat);

        // sanity check value. It can't be larger than the maximum parameter buffer size + id
        // or smaller than the record id
        if ((recordSize > FW_PARAM_BUFFER_MAX_SIZE + sizeof(U32)) or (recordSize < sizeof(U32))) {
            this->log_WARNING_HI_PrmFileReadError(PrmReadError::RECORD_SIZE_VALUE, static_cast<I32>(recordNumTotal),
                                                  static_cast<I32>(recordSize));
            return false;
        }

        // read the parameter ID
        FwPrmIdType parameterId = 0;
        readSize = static_cast<FwSizeType>(sizeof(FwPrmIdType));

        fStat = paramFile.read(buff.getBuffAddr(), readSize, Os::File::WaitType::WAIT);
        if (fStat != Os::File::OP_OK) {
            this->log_WARNING_HI_PrmFileReadError(PrmReadError::PARAMETER_ID, static_cast<I32>(recordNumTotal), fStat);
            return false;
        }
        if (sizeof(parameterId) != static_cast<FwSizeType>(readSize)) {
            this->log_WARNING_HI_PrmFileReadError(PrmReadError::PARAMETER_ID_SIZE, static_cast<I32>(recordNumTotal),
                                                  static_cast<I32>(readSize));
            return false;
        }

        // set serialized size to read parameter ID
        desStat = buff.setBuffLen(static_cast<Fw::Serializable::SizeType>(readSize));
        // should never fail
        FW_ASSERT(Fw::FW_SERIALIZE_OK == desStat, static_cast<FwAssertArgType>(desStat));
        // reset deserialization
        buff.resetDeser();
        // deserialize, since parameter ID is serialized in file
        desStat = buff.deserializeTo(parameterId);
        FW_ASSERT(Fw::FW_SERIALIZE_OK == desStat);

        // copy parameter value from file into a temporary buffer
        Fw::ParamBuffer tmpParamBuffer;  // temporary param buffer to read parameter value from file
        readSize = recordSize - sizeof(parameterId);
        desStat = tmpParamBuffer.setBuffLen(static_cast<Fw::Serializable::SizeType>(readSize));
        FW_ASSERT(Fw::FW_SERIALIZE_OK == desStat, static_cast<FwAssertArgType>(desStat));  // should never fail
        fStat = paramFile.read(tmpParamBuffer.getBuffAddr(), readSize);

        if (fStat != Os::File::OP_OK) {
            this->log_WARNING_HI_PrmFileReadError(PrmReadError::PARAMETER_VALUE, static_cast<I32>(recordNumTotal),
                                                  fStat);
            return false;
        }
        if (static_cast<U32>(readSize) != recordSize - sizeof(parameterId)) {
            this->log_WARNING_HI_PrmFileReadError(PrmReadError::PARAMETER_VALUE_SIZE, static_cast<I32>(recordNumTotal),
                                                  static_cast<I32>(readSize));
            return false;
        }

        // Actually update or add parameter
        FwSizeType index;  // Which index was used for this parameter
        paramUpdateType updateStatus = updateAddPrm(parameterId, tmpParamBuffer, dbType, &index);
        if (updateStatus == PARAM_ADDED) {
            recordNumAdded++;
        } else if (updateStatus == PARAM_UPDATED) {
            recordNumUpdated++;
        }

        if (updateStatus == NO_SLOTS) {
            this->log_FATAL_PrmDbFull(parameterId);
        }

        // set serialized size to read size
        desStat = db[entry].val.setBuffLen(static_cast<Fw::Serializable::SizeType>(readSize));
        // should never fail
        FW_ASSERT(Fw::FW_SERIALIZE_OK == desStat, static_cast<FwAssertArgType>(desStat));
        recordNumTotal++;
    }

    this->log_ACTIVITY_HI_PrmFileLoadComplete(dbString, recordNumTotal, recordNumAdded, recordNumUpdated);
    return true;
}

void PrmDbImpl::pingIn_handler(FwIndexType portNum, U32 key) {
    // respond to ping
    this->pingOut_out(0, key);
}

bool PrmDbImpl::dbEqual() {
    for (FwSizeType i = 0; i < PRMDB_NUM_DB_ENTRIES; i++) {
        if (!(this->m_dbPrime[i] == this->m_dbBackup[i]))
            return false;
    }
    return true;
}

void PrmDbImpl::dbCopy(PrmDbType dest, PrmDbType src) {
    for (FwSizeType i = 0; i < PRMDB_NUM_DB_ENTRIES; i++) {
        dbCopySingle(dest, src, i);
    }
    this->log_ACTIVITY_HI_PrmDbCopyAllComplete(getDbString(src), getDbString(dest));
}

void PrmDbImpl::dbCopySingle(PrmDbType dest, PrmDbType src, FwSizeType index) {
    t_dbStruct* srcPtr;
    t_dbStruct* destPtr;

    getDbPtr(src, &srcPtr);
    getDbPtr(dest, &destPtr);

    FW_ASSERT(index < PRMDB_NUM_DB_ENTRIES);
    destPtr[index].used = srcPtr[index].used;
    destPtr[index].id = srcPtr[index].id;
    destPtr[index].val = srcPtr[index].val;
}

void PrmDbImpl::getDbPtr(PrmDbType dbType, t_dbStruct** dbPtr) {
    FW_ASSERT(dbType == PrmDbType::DB_PRIME or dbType == PrmDbType::DB_BACKUP);
    if (dbType == PrmDbType::DB_PRIME) {
        *dbPtr = this->m_dbPrime;
    } else if (dbType == PrmDbType::DB_BACKUP) {
        *dbPtr = this->m_dbBackup;
    }
}

Fw::String PrmDbImpl::getDbString(PrmDbType dbType) {
    FW_ASSERT(dbType == PrmDbType::DB_PRIME or dbType == PrmDbType::DB_BACKUP);
    if (dbType == PrmDbType::DB_PRIME) {
        return Fw::String("Prime");
    }
    return Fw::String("Backup");
}

}  // namespace Svc
