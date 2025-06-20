// ======================================================================
// \title  Topology.cpp
// \author mstarch
// \brief cpp file containing the topology instantiation code
//
// \copyright
// Copyright 2009-2022, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================
// Provides access to autocoded functions
#include <Ref/Top/RefTopologyAc.hpp>

// Necessary project-specified types
#include <Fw/Types/MallocAllocator.hpp>
#include <Os/Console.hpp>
#include <Svc/FrameAccumulator/FrameDetector/CcsdsTcFrameDetector.hpp>
#include <Ref/Top/Ports_ComPacketQueueEnumAc.hpp>

// Used for 1Hz synthetic cycling
#include <Os/Mutex.hpp>

// Allows easy reference to objects in FPP/autocoder required namespaces
using namespace Ref;

// Instantiate a system logger that will handle Fw::Logger::log calls
Os::Console logger;

// The reference topology uses a malloc-based allocator for components that need to allocate memory during the
// initialization phase.
Fw::MallocAllocator mallocator;

// The reference topology uses the F´ packet protocol when communicating with the ground and therefore uses the F´
// framing and deframing implementations.
Svc::FrameDetectors::CcsdsTcFrameDetector frameDetector;

// The reference topology divides the incoming clock signal (1Hz) into sub-signals: 1Hz, 1/2Hz, and 1/4Hz and
// zero offset for all the dividers
Svc::RateGroupDriver::DividerSet rateGroupDivisorsSet{{{1, 0}, {2, 0}, {4, 0}}};

// Rate groups may supply a context token to each of the attached children whose purpose is set by the project. The
// reference topology sets each token to zero as these contexts are unused in this project.
U32 rateGroup1Context[Svc::ActiveRateGroup::CONNECTION_COUNT_MAX] = {};
U32 rateGroup2Context[Svc::ActiveRateGroup::CONNECTION_COUNT_MAX] = {};
U32 rateGroup3Context[Svc::ActiveRateGroup::CONNECTION_COUNT_MAX] = {};

Svc::ComQueue::QueueConfigurationTable configurationTable;

// A number of constants are needed for construction of the topology. These are specified here.
enum TopologyConstants {
    CMD_SEQ_BUFFER_SIZE = 5 * 1024,
    FILE_DOWNLINK_TIMEOUT = 1000,
    FILE_DOWNLINK_COOLDOWN = 1000,
    FILE_DOWNLINK_CYCLE_TIME = 1000,
    FILE_DOWNLINK_FILE_QUEUE_DEPTH = 10,
    COMM_PRIORITY = 100,
    // Buffer manager for Uplink/Downlink
    COMMS_BUFFER_MANAGER_STORE_SIZE = 2048,
    COMMS_BUFFER_MANAGER_STORE_COUNT = 20,
    COMMS_BUFFER_MANAGER_FILE_STORE_SIZE = 3000,
    COMMS_BUFFER_MANAGER_FILE_QUEUE_SIZE = 30,
    COMMS_BUFFER_MANAGER_ID = 200,
    // Buffer manager for Data Products
    DP_BUFFER_MANAGER_STORE_SIZE = 10000,
    DP_BUFFER_MANAGER_STORE_COUNT = 10,
    DP_BUFFER_MANAGER_ID = 300,
};

/**
 * \brief configure/setup components in project-specific way
 *
 * This is a *helper* function which configures/sets up each component requiring project specific input. This includes
 * allocating resources, passing-in arguments, etc. This function may be inlined into the topology setup function if
 * desired, but is extracted here for clarity.
 */
void configureTopology() {
    // Command sequencer needs to allocate memory to hold contents of command sequences
    cmdSeq.allocateBuffer(0, mallocator, CMD_SEQ_BUFFER_SIZE);

    // Rate group driver needs a divisor list
    rateGroupDriverComp.configure(rateGroupDivisorsSet);

    // Rate groups require context arrays. Empty for Reference example.
    rateGroup1Comp.configure(rateGroup1Context, FW_NUM_ARRAY_ELEMENTS(rateGroup1Context));
    rateGroup2Comp.configure(rateGroup2Context, FW_NUM_ARRAY_ELEMENTS(rateGroup2Context));
    rateGroup3Comp.configure(rateGroup3Context, FW_NUM_ARRAY_ELEMENTS(rateGroup3Context));

    // File downlink requires some project-derived properties.
    fileDownlink.configure(FILE_DOWNLINK_TIMEOUT, FILE_DOWNLINK_COOLDOWN, FILE_DOWNLINK_CYCLE_TIME,
                           FILE_DOWNLINK_FILE_QUEUE_DEPTH);

    // Parameter database is configured with a database file name, and that file must be initially read.
    prmDb.configure("PrmDb.dat");
    prmDb.readParamFile();

    // Buffer managers need a configured set of buckets and an allocator used to allocate memory for those buckets.
    Svc::BufferManager::BufferBins commsBuffMgrBins;
    memset(&commsBuffMgrBins, 0, sizeof(commsBuffMgrBins));
    commsBuffMgrBins.bins[0].bufferSize = COMMS_BUFFER_MANAGER_STORE_SIZE;
    commsBuffMgrBins.bins[0].numBuffers = COMMS_BUFFER_MANAGER_STORE_COUNT;
    commsBuffMgrBins.bins[1].bufferSize = COMMS_BUFFER_MANAGER_FILE_STORE_SIZE;
    commsBuffMgrBins.bins[1].numBuffers = COMMS_BUFFER_MANAGER_FILE_QUEUE_SIZE;
    commsBufferManager.setup(COMMS_BUFFER_MANAGER_ID, 0, mallocator, commsBuffMgrBins);

    Svc::BufferManager::BufferBins dpBuffMgrBins;
    memset(&dpBuffMgrBins, 0, sizeof(dpBuffMgrBins));
    dpBuffMgrBins.bins[0].bufferSize = DP_BUFFER_MANAGER_STORE_SIZE;
    dpBuffMgrBins.bins[0].numBuffers = DP_BUFFER_MANAGER_STORE_COUNT;
    dpBufferManager.setup(DP_BUFFER_MANAGER_ID, 0, mallocator, dpBuffMgrBins);

    frameAccumulator.configure(frameDetector, 1, mallocator, 2048);

    Fw::FileNameString dpDir("./DpCat");
    Fw::FileNameString dpState("./DpCat/DpState.dat");

    // create the DP directory if it doesn't exist
    Os::FileSystem::createDirectory(dpDir.toChar());

    dpCat.configure(&dpDir,1,dpState,0,mallocator);
    dpWriter.configure(dpDir);

    // ComQueue configuration
    // Events (highest-priority)
    configurationTable.entries[Ref::Ports_ComPacketQueue::EVENTS].depth = 100;
    configurationTable.entries[Ref::Ports_ComPacketQueue::EVENTS].priority = 0;
    // Telemetry
    configurationTable.entries[Ref::Ports_ComPacketQueue::TELEMETRY].depth = 500;
    configurationTable.entries[Ref::Ports_ComPacketQueue::TELEMETRY].priority = 2;
    // File Downlink (first entry after the ComPacket queues = NUM_CONSTANTS)
    configurationTable.entries[Ref::Ports_ComPacketQueue::NUM_CONSTANTS].depth = 100;
    configurationTable.entries[Ref::Ports_ComPacketQueue::NUM_CONSTANTS].priority = 1;
    // Allocation identifier is 0 as the MallocAllocator discards it
    comQueue.configure(configurationTable, 0, mallocator);
}

// Public functions for use in main program are namespaced with deployment name Ref
namespace Ref {
void setupTopology(const TopologyState& state) {
    // Autocoded initialization. Function provided by autocoder.
    initComponents(state);
    // Autocoded id setup. Function provided by autocoder.
    setBaseIds();
    // Autocoded connection wiring. Function provided by autocoder.
    connectComponents();
    // Autocoded command registration. Function provided by autocoder.
    regCommands();
    // Autocoded configuration. Function provided by autocoder.
    configComponents(state);
    if (state.hostname != nullptr && state.port != 0) {
        comDriver.configure(state.hostname, state.port);
    }
    // Project-specific component configuration. Function provided above. May be inlined, if desired.
    configureTopology();
    // Autocoded parameter loading. Function provided by autocoder.
    loadParameters();
    // Autocoded task kick-off (active components). Function provided by autocoder.
    startTasks(state);
    // Initialize socket client communication if and only if there is a valid specification
    if (state.hostname != nullptr && state.port != 0) {
        Os::TaskString name("ReceiveTask");
        // Uplink is configured for receive so a socket task is started
        comDriver.start(name, COMM_PRIORITY, Default::STACK_SIZE);
    }
}

void startRateGroups(Fw::TimeInterval interval) {
    // This timer drives the fundamental tick rate of the system.
    // Svc::RateGroupDriver will divide this down to the slower rate groups.
    // This call will block until the stopRateGroups() call is made.
    // For this Linux demo, that call is made from a signal handler.
    linuxTimer.startTimer(interval.getSeconds()*1000+interval.getUSeconds()/1000);
}

void stopRateGroups() {
    linuxTimer.quit();
}

void teardownTopology(const TopologyState& state) {
    // Autocoded (active component) task clean-up. Functions provided by topology autocoder.
    stopTasks(state);
    freeThreads(state);

    // Other task clean-up.
    comDriver.stop();
    (void)comDriver.join();

    // Resource deallocation
    cmdSeq.deallocateBuffer(mallocator);
    commsBufferManager.cleanup();
    frameAccumulator.cleanup();
}
}  // namespace Ref
