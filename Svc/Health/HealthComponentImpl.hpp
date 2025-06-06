// ======================================================================
// \title  Health.hpp
// \author Tim, J.Perez
// \brief  hpp file for Health component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef Health_HPP
#define Health_HPP

#include <Svc/Health/HealthComponentAc.hpp>
#include <Fw/Types/String.hpp>

namespace Svc {

    //!  \class HealthImpl
    //!  \brief Health component implementation class
    //!
    //!  The health component iterates through each entry
    //!  in its table and checks its status. If a ping entry
    //!  tracker is enabled, it will ping its corresponding port
    //!  with a provided key. If a ping return is outstanding,
    //!  a counter is decremented, and its value is checked
    //!  against warning and fault thresholds. A watchdog is
    //!  always stroked in the run handler.

    class HealthImpl final : public HealthComponentBase {

        friend class HealthTester;

        public:
            //!  \brief struct for ping entry
            //!
            //!  struct for ping entry thresholds.
            //!  Countdown is via calls to the run()
            //!  port. If no response by warnCycles,
            //!  an EVR will be generated and telemetry
            //!  count will be updated. If no response
            //!  by fatalCycles, component will send FATAL
            //!  event. A descriptive name is stored in entryName
            //!  for events.
            struct PingEntry {
                FwSizeType warnCycles; //!< number of cycles before WARNING
                FwSizeType fatalCycles; //!< number of cycles before FATAL
                Fw::String entryName; //!< the name of the entry
            };

            //!  \brief HealthImpl constructor
            //!
            //!  The constructor for Health
            //!
            //!  \param compName component name
            HealthImpl(const char * const compName);

            //!  \brief HealthImpl initialization function
            //!
            //!  Initializes the autocoded base class, ping table, and data members
            //!
            //!  \param queueDepth Depth of queue
            //!  \param instance The instance number
            void init(const FwSizeType queueDepth, const FwEnumStoreType instance);

            //! \brief Set ping entry tables
            //!
            //! Provides a table of ping entries
            //!
            //!  \param pingEntries Pointer to provided ping table entries
            //!  \param numPingEntries Number of ping entries in table
            //!  \param watchDogCode Value that is sent to watchdog
            void setPingEntries(PingEntry* pingEntries, FwIndexType numPingEntries, U32 watchDogCode);

            //!  \brief Component destructor
            //!
            //!  The destructor for HealthImpl is empty
            ~HealthImpl();

        protected:

            //!  \brief additional checks function
            //!
            //!  Does additional checks based on the platform
            virtual void doOtherChecks();

        private:

            //!  \brief ping return handler
            //!
            //!  Handler implementation for pingReturn
            //!
            //!  \param portNum Port number
            //!  \param key Key value
            void PingReturn_handler(const FwIndexType portNum, U32 key);

            //!  \brief run handler
            //!
            //!  Handler implementation for run
            //!
            //!  \param portNum Port number
            //!  \param context Port Context
            void Run_handler(const FwIndexType portNum, U32 context);

            //!  \brief HLTH_ENABLE handler
            //!
            //!  Implementation for HLTH_ENABLE command handler
            //!
            //!  \param opCode Command opcode
            //!  \param cmdSeq Command sequence
            //!  \param enable Enum for enabling/disabling tracker
            void HLTH_ENABLE_cmdHandler(const FwOpcodeType opCode, U32 cmdSeq, Fw::Enabled enable);

            //!  \brief HLTH_PING_ENABLE handler
            //!
            //!  Handler for command HLTH_PING_ENABLE
            //!
            //!  \param opCode Command opcode
            //!  \param cmdSeq Command sequence
            //!  \param entry Ping entry number
            //!  \param enable Enum for enabling/disabling tracker
            void HLTH_PING_ENABLE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdStringArg& entry, Fw::Enabled enable);

            //!  \brief HLTH_CHNG_PING handler
            //!
            //!  Implementation for HLTH_CHNG_PING command handler
            //!
            //!  \param opCode Command opcode
            //!  \param cmdSeq Command sequence
            //!  \param entry Ping entry number
            //!  \param warningValue Warning threshold value
            //!  \param fatalValue Fatal threshold value
            void HLTH_CHNG_PING_cmdHandler(const FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdStringArg& entry, U32 warningValue, U32 fatalValue);

            //!  \brief ping tracker struct
            //!
            //!  Array for storing ping table entries
            struct PingTracker {
                PingEntry entry; //!< entry passed by user
                U32 cycleCount; //!< current cycle count
                U32 key; //!< key passed to ping
                Fw::Enabled::t enabled; //!< if current ping result is checked
            } m_pingTrackerEntries[NUM_PINGSEND_OUTPUT_PORTS];

            FwIndexType findEntry(const Fw::CmdStringArg& entry);

            //!  Private member data
            FwIndexType m_numPingEntries; //!< stores number of entries passed to constructor
            U32 m_key; //!< current key value. Just increments for each ping entry.
            U32 m_watchDogCode; //!< stores code used for watchdog stroking
            U32 m_warnings; //!< number of slip warnings issued
            Fw::Enabled m_enabled; //!< if the pinger is enabled
            FwSizeType queue_depth; //!< queue depth passed by user

    };

} // end namespace Svc

#endif
