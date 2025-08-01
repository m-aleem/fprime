/*
 * PrmDbImpl.cpp
 *
 *  Created on: March 9, 2015
 *      Author: Timothy Canham
 */

#include <Svc/PrmDb/PrmDbImpl.hpp>
#include <Fw/Types/Assert.hpp>

#include <Os/File.hpp>

#include <cstring>
#include <cstdio>

static_assert(std::numeric_limits<FwSizeType>::max() >= PRMDB_NUM_DB_ENTRIES, "PRMDB_NUM_DB_ENTRIES must fit within range of FwSizeType");

namespace Svc {


    typedef PrmDb_PrmWriteError PrmWriteError;
    typedef PrmDb_PrmReadError PrmReadError;
    // anonymous namespace for buffer declaration
    namespace {
        class WorkingBuffer : public Fw::SerializeBufferBase {
            public:

                FwSizeType getBuffCapacity() const {
                    return sizeof(m_buff);
                }

                U8* getBuffAddr() {
                    return m_buff;
                }

                const U8* getBuffAddr() const {
                    return m_buff;
                }

            private:
                // Set to max of parameter buffer + id
                U8 m_buff[FW_PARAM_BUFFER_MAX_SIZE + sizeof(FwPrmIdType)];
        };
    }

    PrmDbImpl::PrmDbImpl(const char* name) : PrmDbComponentBase(name) {
        this->clearDb();
    }

    void PrmDbImpl::configure(const char* file) {
        FW_ASSERT(file != nullptr);
        this->m_fileName = file;
    }

    void PrmDbImpl::clearDb() {
        for (FwSizeType entry = 0; entry < PRMDB_NUM_DB_ENTRIES; entry++) {
            this->m_db[entry].used = false;
            this->m_db[entry].id = 0;
        }
    }

    // If ports are no longer guarded, these accesses need to be protected from each other
    // If there are a lot of accesses, perhaps an interrupt lock could be used instead of guarded ports

    Fw::ParamValid PrmDbImpl::getPrm_handler(FwIndexType portNum, FwPrmIdType id, Fw::ParamBuffer &val) {
        // search for entry
        Fw::ParamValid stat = Fw::ParamValid::INVALID;

        for (FwSizeType entry = 0; entry < PRMDB_NUM_DB_ENTRIES; entry++) {
            if (this->m_db[entry].used) {
                if (this->m_db[entry].id == id) {
                    val = this->m_db[entry].val;
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

    void PrmDbImpl::setPrm_handler(FwIndexType portNum, FwPrmIdType id, Fw::ParamBuffer &val) {

        this->lock();

        // search for existing entry

        bool existingEntry = false;
        bool noSlots = true;

        for (FwSizeType entry = 0; entry < PRMDB_NUM_DB_ENTRIES; entry++) {
            if ((this->m_db[entry].used) && (id == this->m_db[entry].id)) {
                this->m_db[entry].val = val;
                existingEntry = true;
                break;
            }
        }

        // if there is no existing entry, add one
        if (!existingEntry) {
            for (FwSizeType entry = 0; entry < PRMDB_NUM_DB_ENTRIES; entry++) {
                if (!(this->m_db[entry].used)) {
                    this->m_db[entry].val = val;
                    this->m_db[entry].id = id;
                    this->m_db[entry].used = true;
                    noSlots = false;
                    break;
                }
            }
        }

        this->unLock();

        if (existingEntry) {
            this->log_ACTIVITY_HI_PrmIdUpdated(id);
        } else if (noSlots) {
            this->log_FATAL_PrmDbFull(id);
        } else {
            this->log_ACTIVITY_HI_PrmIdAdded(id);
        }

    }

    void PrmDbImpl::PRM_SAVE_FILE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
        FW_ASSERT(this->m_fileName.length() > 0);
        Os::File paramFile;
        WorkingBuffer buff;

        Os::File::Status stat = paramFile.open(this->m_fileName.toChar(),Os::File::OPEN_WRITE);
        if (stat != Os::File::OP_OK) {
            this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::OPEN,0,stat);
            this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
            return;
        }

        this->lock();

        // Traverse the parameter list, saving each entry

        U32 numRecords = 0;

        for (FwSizeType entry = 0; entry < FW_NUM_ARRAY_ELEMENTS(this->m_db); entry++) {
            if (this->m_db[entry].used) {
                // write delimiter
                static const U8 delim = PRMDB_ENTRY_DELIMITER;
                FwSizeType writeSize = static_cast<FwSizeType>(sizeof(delim));
                stat = paramFile.write(&delim,writeSize,Os::File::WaitType::WAIT);
                if (stat != Os::File::OP_OK) {
                    this->unLock();
                    this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::DELIMITER,static_cast<I32>(numRecords),stat);
                    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
                    return;
                }
                if (writeSize != sizeof(delim)) {
                    this->unLock();
                    this->log_WARNING_HI_PrmFileWriteError(
                        PrmWriteError::DELIMITER_SIZE,
                        static_cast<I32>(numRecords),
                        static_cast<I32>(writeSize));
                    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
                    return;
                }
                // serialize record size = id field + data
                U32 recordSize = static_cast<U32>(sizeof(FwPrmIdType) + this->m_db[entry].val.getBuffLength());

                // reset buffer
                buff.resetSer();
                Fw::SerializeStatus serStat = buff.serialize(recordSize);
                // should always work
                FW_ASSERT(Fw::FW_SERIALIZE_OK == serStat,static_cast<FwAssertArgType>(serStat));

                // write record size
                writeSize = static_cast<FwSizeType>(buff.getBuffLength());
                stat = paramFile.write(buff.getBuffAddr(),writeSize,Os::File::WaitType::WAIT);
                if (stat != Os::File::OP_OK) {
                    this->unLock();
                    this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::RECORD_SIZE,static_cast<I32>(numRecords),stat);
                    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
                    return;
                }
                if (writeSize != sizeof(recordSize)) {
                    this->unLock();
                    this->log_WARNING_HI_PrmFileWriteError(
                        PrmWriteError::RECORD_SIZE_SIZE,
                        static_cast<I32>(numRecords),
                        static_cast<I32>(writeSize));
                    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
                    return;
                }

                // reset buffer
                buff.resetSer();

                // serialize parameter id

                serStat = buff.serialize(this->m_db[entry].id);
                // should always work
                FW_ASSERT(Fw::FW_SERIALIZE_OK == serStat,static_cast<FwAssertArgType>(serStat));

                // write parameter ID
                writeSize = static_cast<FwSizeType>(buff.getBuffLength());
                stat = paramFile.write(buff.getBuffAddr(),writeSize,Os::File::WaitType::WAIT);
                if (stat != Os::File::OP_OK) {
                    this->unLock();
                    this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::PARAMETER_ID,static_cast<I32>(numRecords),stat);
                    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
                    return;
                }
                if (writeSize != static_cast<FwSizeType>(buff.getBuffLength())) {
                    this->unLock();
                    this->log_WARNING_HI_PrmFileWriteError(
                        PrmWriteError::PARAMETER_ID_SIZE,
                        static_cast<I32>(numRecords),
                        static_cast<I32>(writeSize));
                    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
                    return;
                }

                // write serialized parameter value

                writeSize = static_cast<FwSizeType>(this->m_db[entry].val.getBuffLength());
                stat = paramFile.write(this->m_db[entry].val.getBuffAddr(),writeSize,Os::File::WaitType::WAIT);
                if (stat != Os::File::OP_OK) {
                    this->unLock();
                    this->log_WARNING_HI_PrmFileWriteError(PrmWriteError::PARAMETER_VALUE,static_cast<I32>(numRecords),stat);
                    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
                    return;
                }
                if (writeSize != static_cast<FwSizeType>(this->m_db[entry].val.getBuffLength())) {
                    this->unLock();
                    this->log_WARNING_HI_PrmFileWriteError(
                        PrmWriteError::PARAMETER_VALUE_SIZE,
                        static_cast<I32>(numRecords),
                        static_cast<I32>(writeSize));
                    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
                    return;
                }
                numRecords++;
            } // end if record in use
        } // end for each record

        this->unLock();
        this->log_ACTIVITY_HI_PrmFileSaveComplete(numRecords);
        this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);

    }

    PrmDbImpl::~PrmDbImpl() {
    }

    void PrmDbImpl::readParamFile() {
        FW_ASSERT(this->m_fileName.length() > 0);
        // load file. FIXME: Put more robust file checking, such as a CRC.
        Os::File paramFile;

        Os::File::Status stat = paramFile.open(this->m_fileName.toChar(),Os::File::OPEN_READ);
        if (stat != Os::File::OP_OK) {
            this->log_WARNING_HI_PrmFileReadError(PrmReadError::OPEN,0,stat);
            return;
        }

        WorkingBuffer buff;

        U32 recordNum = 0;

        this->clearDb();

        for (FwSizeType entry = 0; entry < PRMDB_NUM_DB_ENTRIES; entry++)  {

            U8 delimiter;
            FwSizeType readSize = static_cast<FwSizeType>(sizeof(delimiter));

            // read delimiter
            Os::File::Status fStat = paramFile.read(&delimiter,readSize,Os::File::WaitType::WAIT);

            // check for end of file (read size 0)
            if (0 == readSize) {
                break;
            }

            if (fStat != Os::File::OP_OK) {
                this->log_WARNING_HI_PrmFileReadError(PrmReadError::DELIMITER,static_cast<I32>(recordNum),fStat);
                return;
            }

            if (sizeof(delimiter) != readSize) {
                this->log_WARNING_HI_PrmFileReadError(PrmReadError::DELIMITER_SIZE,static_cast<I32>(recordNum),static_cast<I32>(readSize));
                return;
            }

            if (PRMDB_ENTRY_DELIMITER != delimiter) {
                this->log_WARNING_HI_PrmFileReadError(PrmReadError::DELIMITER_VALUE,static_cast<I32>(recordNum),delimiter);
                return;
            }

            U32 recordSize = 0;
            // read record size
            readSize = sizeof(recordSize);

            fStat = paramFile.read(buff.getBuffAddr(),readSize,Os::File::WaitType::WAIT);
            if (fStat != Os::File::OP_OK) {
                this->log_WARNING_HI_PrmFileReadError(PrmReadError::RECORD_SIZE,static_cast<I32>(recordNum),fStat);
                return;
            }
            if (sizeof(recordSize) != readSize) {
                this->log_WARNING_HI_PrmFileReadError(PrmReadError::RECORD_SIZE_SIZE,static_cast<I32>(recordNum),static_cast<I32>(readSize));
                return;
            }
            // set serialized size to read size
            Fw::SerializeStatus desStat = buff.setBuffLen(static_cast<Fw::Serializable::SizeType>(readSize));
            // should never fail
            FW_ASSERT(Fw::FW_SERIALIZE_OK == desStat,static_cast<FwAssertArgType>(desStat));
            // reset deserialization
            buff.resetDeser();
            // deserialize, since record size is serialized in file
            desStat = buff.deserializeTo(recordSize);
            FW_ASSERT(Fw::FW_SERIALIZE_OK == desStat);

            // sanity check value. It can't be larger than the maximum parameter buffer size + id
            // or smaller than the record id
            if ((recordSize > FW_PARAM_BUFFER_MAX_SIZE + sizeof(U32)) or (recordSize < sizeof(U32))) {
                this->log_WARNING_HI_PrmFileReadError(PrmReadError::RECORD_SIZE_VALUE,static_cast<I32>(recordNum),static_cast<I32>(recordSize));
                return;
            }

            // read the parameter ID
            FwPrmIdType parameterId = 0;
            readSize = static_cast<FwSizeType>(sizeof(FwPrmIdType));

            fStat = paramFile.read(buff.getBuffAddr(),readSize,Os::File::WaitType::WAIT);
            if (fStat != Os::File::OP_OK) {
                this->log_WARNING_HI_PrmFileReadError(PrmReadError::PARAMETER_ID,static_cast<I32>(recordNum),fStat);
                return;
            }
            if (sizeof(parameterId) != static_cast<FwSizeType>(readSize)) {
                this->log_WARNING_HI_PrmFileReadError(PrmReadError::PARAMETER_ID_SIZE,static_cast<I32>(recordNum),static_cast<I32>(readSize));
                return;
            }

            // set serialized size to read parameter ID
            desStat = buff.setBuffLen(static_cast<Fw::Serializable::SizeType>(readSize));
            // should never fail
            FW_ASSERT(Fw::FW_SERIALIZE_OK == desStat,static_cast<FwAssertArgType>(desStat));
            // reset deserialization
            buff.resetDeser();
            // deserialize, since parameter ID is serialized in file
            desStat = buff.deserializeTo(parameterId);
            FW_ASSERT(Fw::FW_SERIALIZE_OK == desStat);

            // copy parameter
            this->m_db[entry].used = true;
            this->m_db[entry].id = parameterId;
            readSize = recordSize-sizeof(parameterId);

            fStat = paramFile.read(this->m_db[entry].val.getBuffAddr(),readSize);

            if (fStat != Os::File::OP_OK) {
                this->log_WARNING_HI_PrmFileReadError(PrmReadError::PARAMETER_VALUE,static_cast<I32>(recordNum),fStat);
                return;
            }
            if (static_cast<U32>(readSize) != recordSize-sizeof(parameterId)) {
                this->log_WARNING_HI_PrmFileReadError(PrmReadError::PARAMETER_VALUE_SIZE,static_cast<I32>(recordNum),static_cast<I32>(readSize));
                return;
            }

            // set serialized size to read size
            desStat = this->m_db[entry].val.setBuffLen(static_cast<Fw::Serializable::SizeType>(readSize));
            // should never fail
            FW_ASSERT(Fw::FW_SERIALIZE_OK == desStat,static_cast<FwAssertArgType>(desStat));
            recordNum++;

        }

        this->log_ACTIVITY_HI_PrmFileLoadComplete(recordNum);
    }

    void PrmDbImpl::pingIn_handler(FwIndexType portNum, U32 key) {
        // respond to ping
        this->pingOut_out(0,key);
    }



}
