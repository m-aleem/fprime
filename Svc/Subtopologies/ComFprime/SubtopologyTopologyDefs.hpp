#ifndef COMFPRIMESUBTOPOLOGY_DEFS_HPP
#define COMFPRIMESUBTOPOLOGY_DEFS_HPP

#include <Svc/FrameAccumulator/FrameDetector/FprimeFrameDetector.hpp>
#include <Fw/Types/MallocAllocator.hpp>
#include <Svc/BufferManager/BufferManager.hpp>
#include "Svc/Subtopologies/ComFprime/ComFprimeConfig/FppConstantsAc.hpp"
#include "ComFprimeConfig/ComFprimeSubtopologyConfig.hpp"

namespace ComFprime {
    struct SubtopologyState {
        // Empty - no external state needed for ComFprime subtopology
    };

    struct TopologyState {
        SubtopologyState comFprime;
    };
}

#endif
