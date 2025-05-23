####
# Darwin.cmake:
#
# Darwin based platform file used for Darwin (Mac OS X) targets. Note: this sets some OS X flags before calling into the common
# Linux implementations to use the posix types defined there.
####
add_definitions(-DTGT_OS_TYPE_DARWIN)

set(FPRIME_USE_POSIX ON)
set(FPRIME_HAS_SOCKETS ON)
# Set platform default for stubbed drivers
if (NOT DEFINED FPRIME_USE_STUBBED_DRIVERS)
   set(FPRIME_USE_STUBBED_DRIVERS ON)
endif()

# Set platform default for baremetal scheduler drivers
if (NOT DEFINED FPRIME_USE_BAREMETAL_SCHEDULER)
   set(FPRIME_USE_BAREMETAL_SCHEDULER OFF)
   message(STATUS "Requiring thread library")
   FIND_PACKAGE ( Threads REQUIRED )
endif()
choose_fprime_implementation(Os/File Os/File/Posix)
choose_fprime_implementation(Os/Console Os/Console/Posix)
choose_fprime_implementation(Os/Task Os/Task/Posix)
choose_fprime_implementation(Os/Mutex Os/Mutex/Posix)
choose_fprime_implementation(Os/Queue Os/Generic/PriorityQueue)
choose_fprime_implementation(Os/RawTime Os/RawTime/Posix)

choose_fprime_implementation(Os/Cpu Os/Cpu/Darwin)
choose_fprime_implementation(Os/Memory Os/Memory/Darwin)

# Add unix include path which is compatible with Darwin for PlatformTypes.hpp
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/unix/Platform/")
