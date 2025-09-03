/**
 * \file
 * \author T.Canham
 * \brief Component for managing parameters
 *
 * \copyright
 * Copyright 2009-2015, by the California Institute of Technology.
 * ALL RIGHTS RESERVED.  United States Government Sponsorship
 * acknowledged.
 * <br /><br />
 */

#ifndef PRMDBIMPL_HPP_
#define PRMDBIMPL_HPP_

#include <Fw/Types/String.hpp>
#include <Os/Mutex.hpp>
#include <Svc/PrmDb/PrmDbComponentAc.hpp>
#include <config/PrmDbImplCfg.hpp>

namespace Svc {

//! \class PrmDbImpl
//! \brief Component class for managing parameters
//!
//! This component supports storing, setting and saving of serialized parameters
//! for components.
//!

class PrmDbImpl final : public PrmDbComponentBase {

  friend class PrmDbTester;

  public:

    //!  \brief PrmDb constructor
    //!
    //!  The constructor for the PrmDbImpl class.
    //!   The constructor clears the database and stores
    //!   the file name for opening later.
    //!
    //!  \param name component instance name
    PrmDbImpl(const char* name);

    //!  \brief PrmDb configure method
    //!
    //!  The configure method stores the file name for opening later.
    //!
    //!  \param file file where parameters are stored.
    void configure(const char* file);

    //!  \brief PrmDb file read function
    //!
    //!  The readFile function reads the set of parameters from the file passed in to
    //!  the constructor.
    //!
    void readParamFile();  // NOTE: Assumed to run at initialization time. No guard of data structure.

    //!  \brief PrmDb destructor
    //!
    virtual ~PrmDbImpl();


    enum paramUpdateType {
      NO_SLOTS,
      PARAM_ADDED,
      PARAM_UPDATED,
      MAX_PARAM_UPDATE_TYPES
    };

  protected:
  private:
    struct t_dbStruct {
        bool used;            //!< whether slot is being used
        FwPrmIdType id;       //!< the id being stored in the slot
        Fw::ParamBuffer val;  //!< the serialized value of the parameter

        bool operator==(const t_dbStruct& other) const {
          if (used != other.used) return false;
          if (id != other.id) return false;
          // Compare lengths first
          if (val.getBuffLength() != other.val.getBuffLength()) return false;
          // Compare buffer contents
          return std::memcmp(val.getBuffAddr(), other.val.getBuffAddr(), val.getBuffLength()) == 0;
        }
    };

    //! \brief Check param db equality
    //!
    //!  This helper method verifies the prime and backup parameter dbs are equal
    bool dbEqual();

    //! \brief Deep copy for db
    //!
    //!  Copies one db to another
    void dbCopy(t_dbStruct* dest, t_dbStruct* src);

    //! \brief Read a parameter file and apply the values to the database
    //!
    //!  This method reads a parameter file and applies the values to the database.
    //!
    //!  \param fileName The name of the parameter file to read
    //!  \param db Pointer to the database array to populate with parameter data
    //!  \return status success (True)/failure(False)
    bool readParamFileImpl(const Fw::StringBase& fileName, t_dbStruct* db, Fw::String dbString);

    //!  \brief PrmDb parameter get handler
    //!
    //!  This function retrieves a parameter value from the loaded set of stored parameters
    //!
    //!  \param portNum input port number. Should always be zero
    //!  \param id identifier for parameter being used.
    //!  \param val buffer where value is placed.
    //!  \return status of retrieval. PARAM_VALID = successful read, PARAM_INVALID = unsuccessful read
    Fw::ParamValid getPrm_handler(FwIndexType portNum, FwPrmIdType id, Fw::ParamBuffer& val);

    //!  \brief PrmDb parameter set handler
    //!
    //!  This function updates the value of the parameter stored in RAM. The PRM_SAVE_FILE
    //!  must be called to save the value to a file.
    //!
    //!  \param portNum input port number. Should always be zero
    //!  \param id identifier for parameter being used.
    //!  \param val buffer where value to be saved is stored.
    void setPrm_handler(FwIndexType portNum, FwPrmIdType id, Fw::ParamBuffer& val);


    //!  \brief PrmDb parameter add or update (set) helper
    //!
    //!  This function does the underlying parameter update
    //!
    //!  \param id identifier for parameter being used.
    //!  \param val buffer where value to be saved is stored.
    PrmDbImpl::paramUpdateType updateAddPrm(FwPrmIdType id, Fw::ParamBuffer& val, t_dbStruct* db);

    //!  \brief component ping handler
    //!
    //!  The ping handler responds to messages to verify that the task
    //!  is still executing. Will call output ping port
    //!
    //!  \param portNum the number of the incoming port.
    //!  \param opCode the opcode being registered.
    //!  \param key the key value that is returned with the ping response
    void pingIn_handler(FwIndexType portNum, U32 key);

    //!  \brief PrmDb PRM_SAVE_FILE command handler
    //!
    //!  This function saves the parameter values stored in RAM to the file
    //!  specified in the constructor. Any updates to parameters are not saved
    //!  until this function is called.
    //!
    //!  \param opCode The opcode of this commands
    //!  \param cmdSeq The sequence number of the command
    void PRM_SAVE_FILE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq);

    //!  \brief PrmDb PRM_SAVE_FILE command handler
    //!
    //!  This function applies the parameter values from a specified
    //!  file into the the RAM parameter values. Note that these updates
    //!  are not saved until a subsequent call to SAVE file.
    //!
    //!  \param opCode The opcode of this commands
    //!  \param cmdSeq The sequence number of the command
    //!  \param fileName The name of the parameter load file
    void PRM_SET_FILE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdStringArg& fileName);

    //!  \brief PrmDb clear database function
    //!
    //!  This function clears all entries from the RAM database
    //!
    //!  \param db Pointer to the database array to clear

    void clearDb(t_dbStruct* db);  //!< clear the parameter database

    Fw::String m_fileName;  //!< filename for parameter storage

    t_dbStruct m_db[PRMDB_NUM_DB_ENTRIES];
    t_dbStruct m_dbBackup[PRMDB_NUM_DB_ENTRIES];
};
}  // namespace Svc

#endif /* PRMDBIMPL_HPP_ */
