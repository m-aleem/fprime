#ifndef RPITopologyDefs_HPP
#define RPITopologyDefs_HPP

#include "Fw/Types/MallocAllocator.hpp"
#include "Os/Console.hpp"
#include "RPI/Top/FppConstantsAc.hpp"
#include "Svc/LinuxTimer/LinuxTimer.hpp"
#include <Svc/FrameAccumulator/FrameDetector/FprimeFrameDetector.hpp>

namespace RPI {

  namespace Allocation {

    // Malloc allocator for topology construction
    extern Fw::MallocAllocator mallocator;

  }

  namespace Init {

    // Initialization status
    extern bool status;

  }

  // State for topology construction
  struct TopologyState {
    TopologyState() :
      hostName(nullptr),
      portNumber(0)
    {

    }
    TopologyState(
        const char *a_hostName,
        U16 a_portNumber
    ) :
      hostName(a_hostName),
      portNumber(a_portNumber)
    {

    }
    const char* hostName;
    U16 portNumber;
  };

  // Health ping entries
  namespace PingEntries {
    namespace RPI_rateGroup10HzComp { enum { WARN = 3, FATAL = 5 }; }
    namespace RPI_rateGroup1HzComp { enum { WARN = 3, FATAL = 5 }; }
    namespace RPI_cmdDisp { enum { WARN = 3, FATAL = 5 }; }
    namespace RPI_cmdSeq { enum { WARN = 3, FATAL = 5 }; }
    namespace RPI_chanTlm { enum { WARN = 3, FATAL = 5 }; }
    namespace RPI_eventLogger { enum { WARN = 3, FATAL = 5 }; }
    namespace RPI_prmDb { enum { WARN = 3, FATAL = 5 }; }
    namespace RPI_fileDownlink { enum { WARN = 3, FATAL = 5 }; }
    namespace RPI_fileUplink { enum { WARN = 3, FATAL = 5 }; }
  }

}

#endif
