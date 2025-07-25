/*
 * TestCommand1Impl.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: tcanham
 */

#include <cstdio>

#include <Fw/Types/Assert.hpp>
#include <Os/File.hpp>
#include <Svc/EventManager/EventManager.hpp>

namespace Svc {
static_assert(std::numeric_limits<FwSizeType>::max() >= TELEM_ID_FILTER_SIZE,
              "TELEM_ID_FILTER_SIZE must fit within range of FwSizeType");
typedef EventManager_Enabled Enabled;
typedef EventManager_FilterSeverity FilterSeverity;

EventManager::EventManager(const char* name) : EventManagerComponentBase(name) {
    // set filter defaults
    this->m_filterState[FilterSeverity::WARNING_HI].enabled =
        FILTER_WARNING_HI_DEFAULT ? Enabled::ENABLED : Enabled::DISABLED;
    this->m_filterState[FilterSeverity::WARNING_LO].enabled =
        FILTER_WARNING_LO_DEFAULT ? Enabled::ENABLED : Enabled::DISABLED;
    this->m_filterState[FilterSeverity::COMMAND].enabled =
        FILTER_COMMAND_DEFAULT ? Enabled::ENABLED : Enabled::DISABLED;
    this->m_filterState[FilterSeverity::ACTIVITY_HI].enabled =
        FILTER_ACTIVITY_HI_DEFAULT ? Enabled::ENABLED : Enabled::DISABLED;
    this->m_filterState[FilterSeverity::ACTIVITY_LO].enabled =
        FILTER_ACTIVITY_LO_DEFAULT ? Enabled::ENABLED : Enabled::DISABLED;
    this->m_filterState[FilterSeverity::DIAGNOSTIC].enabled =
        FILTER_DIAGNOSTIC_DEFAULT ? Enabled::ENABLED : Enabled::DISABLED;

    memset(m_filteredIDs, 0, sizeof(m_filteredIDs));
}

EventManager::~EventManager() {}

void EventManager::LogRecv_handler(FwIndexType portNum,
                                   FwEventIdType id,
                                   Fw::Time& timeTag,
                                   const Fw::LogSeverity& severity,
                                   Fw::LogBuffer& args) {
    // make sure ID is not zero. Zero is reserved for ID filter.
    FW_ASSERT(id != 0);

    switch (severity.e) {
        case Fw::LogSeverity::FATAL:  // always pass FATAL
            break;
        case Fw::LogSeverity::WARNING_HI:
            if (this->m_filterState[FilterSeverity::WARNING_HI].enabled == Enabled::DISABLED) {
                return;
            }
            break;
        case Fw::LogSeverity::WARNING_LO:
            if (this->m_filterState[FilterSeverity::WARNING_LO].enabled == Enabled::DISABLED) {
                return;
            }
            break;
        case Fw::LogSeverity::COMMAND:
            if (this->m_filterState[FilterSeverity::COMMAND].enabled == Enabled::DISABLED) {
                return;
            }
            break;
        case Fw::LogSeverity::ACTIVITY_HI:
            if (this->m_filterState[FilterSeverity::ACTIVITY_HI].enabled == Enabled::DISABLED) {
                return;
            }
            break;
        case Fw::LogSeverity::ACTIVITY_LO:
            if (this->m_filterState[FilterSeverity::ACTIVITY_LO].enabled == Enabled::DISABLED) {
                return;
            }
            break;
        case Fw::LogSeverity::DIAGNOSTIC:
            if (this->m_filterState[FilterSeverity::DIAGNOSTIC].enabled == Enabled::DISABLED) {
                return;
            }
            break;
        default:
            FW_ASSERT(0, static_cast<FwAssertArgType>(severity.e));
            return;
    }

    // check ID filters
    for (FwSizeType entry = 0; entry < TELEM_ID_FILTER_SIZE; entry++) {
        if ((m_filteredIDs[entry] == id) && (severity != Fw::LogSeverity::FATAL)) {
            return;
        }
    }

    // send event to the logger thread
    this->loqQueue_internalInterfaceInvoke(id, timeTag, severity, args);

    // if connected, announce the FATAL
    if (Fw::LogSeverity::FATAL == severity.e) {
        if (this->isConnected_FatalAnnounce_OutputPort(0)) {
            this->FatalAnnounce_out(0, id);
        }
    }
}

void EventManager::loqQueue_internalInterfaceHandler(FwEventIdType id,
                                                     const Fw::Time& timeTag,
                                                     const Fw::LogSeverity& severity,
                                                     const Fw::LogBuffer& args) {
    // Serialize event
    this->m_logPacket.setId(id);
    this->m_logPacket.setTimeTag(timeTag);
    this->m_logPacket.setLogBuffer(args);
    this->m_comBuffer.resetSer();
    Fw::SerializeStatus stat = this->m_logPacket.serialize(this->m_comBuffer);
    FW_ASSERT(Fw::FW_SERIALIZE_OK == stat, static_cast<FwAssertArgType>(stat));

    if (this->isConnected_PktSend_OutputPort(0)) {
        this->PktSend_out(0, this->m_comBuffer, 0);
    }
}

void EventManager::SET_EVENT_FILTER_cmdHandler(FwOpcodeType opCode,
                                               U32 cmdSeq,
                                               FilterSeverity filterLevel,
                                               Enabled filterEnable) {
    this->m_filterState[filterLevel.e].enabled = filterEnable;
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void EventManager::SET_ID_FILTER_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                            U32 cmdSeq,           //!< The command sequence number
                                            FwEventIdType ID,
                                            Enabled idEnabled  //!< ID filter state
) {
    if (Enabled::ENABLED == idEnabled.e) {  // add ID
        // search list for existing entry
        for (FwSizeType entry = 0; entry < TELEM_ID_FILTER_SIZE; entry++) {
            if (this->m_filteredIDs[entry] == ID) {
                this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
                this->log_ACTIVITY_HI_ID_FILTER_ENABLED(ID);
                return;
            }
        }
        // if not already a match, search for an open slot
        for (FwSizeType entry = 0; entry < TELEM_ID_FILTER_SIZE; entry++) {
            if (this->m_filteredIDs[entry] == 0) {
                this->m_filteredIDs[entry] = ID;
                this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
                this->log_ACTIVITY_HI_ID_FILTER_ENABLED(ID);
                return;
            }
        }
        // if an empty slot was not found, send an error event
        this->log_WARNING_LO_ID_FILTER_LIST_FULL(ID);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
    } else {  // remove ID
        // search list for existing entry
        for (FwSizeType entry = 0; entry < TELEM_ID_FILTER_SIZE; entry++) {
            if (this->m_filteredIDs[entry] == ID) {
                this->m_filteredIDs[entry] = 0;  // zero entry
                this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
                this->log_ACTIVITY_HI_ID_FILTER_REMOVED(ID);
                return;
            }
        }
        // if it gets here, wasn't found
        this->log_WARNING_LO_ID_FILTER_NOT_FOUND(ID);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
    }
}

void EventManager::DUMP_FILTER_STATE_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                                U32 cmdSeq            //!< The command sequence number
) {
    // first, iterate through severity filters
    for (FwEnumStoreType filter = 0; filter < FilterSeverity::NUM_CONSTANTS; filter++) {
        FilterSeverity filterState(static_cast<FilterSeverity::t>(filter));
        this->log_ACTIVITY_LO_SEVERITY_FILTER_STATE(filterState,
                                                    Enabled::ENABLED == this->m_filterState[filter].enabled.e);
    }

    // iterate through ID filter
    for (FwSizeType entry = 0; entry < TELEM_ID_FILTER_SIZE; entry++) {
        if (this->m_filteredIDs[entry] != 0) {
            this->log_ACTIVITY_HI_ID_FILTER_ENABLED(this->m_filteredIDs[entry]);
        }
    }

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void EventManager::pingIn_handler(const FwIndexType portNum, U32 key) {
    // return key
    this->pingOut_out(0, key);
}

}  // namespace Svc
