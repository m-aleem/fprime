# Option to select atomic implementation
# 0: Standard library implementation (default)
# 1: Mutex-based custom implementation
# 2: Reserved for future implementation (e.g., platform-specific lockless)
set(STD_ATOMIC_IMPL "0" CACHE STRING "Select atomic implementation: 0=standard, 1=mutex-based, 2=reserved")

# Register the module
register_fprime_module(
    Os_std
    HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/atomic.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/custom/atomic_mutex.hpp"
    SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/empty.cpp"
    DEPENDS
        Fw_Types
)

# Pass the STD_ATOMIC_IMPL option to the compiler
target_compile_definitions(Os_std PUBLIC STD_ATOMIC_IMPL=${STD_ATOMIC_IMPL})

# Unit tests
register_fprime_ut(
    Os_std_ut
  SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestAtomic.cpp"
  DEPENDS
    Fw_Types
)