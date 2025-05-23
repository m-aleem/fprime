/*
 * StaticMemoryCfg.hpp:
 *
 * Configuration settings for the static memory component.
 */

#ifndef SVC_STATIC_MEMORY_CFG_HPP_
#define SVC_STATIC_MEMORY_CFG_HPP_
const bool MY_LIBRARY_OVERRIDE = true;

namespace Svc {
    enum StaticMemoryConfig {
        STATIC_MEMORY_ALLOCATION_SIZE = 2048
    };
}

#endif

