# Os/std

These files provide custom implementations for portions of the C++ Standard
Library (in namespace std) for platforms which do not have native support.

## atomic

## Background

Custom partial implementations for `std::atomic`.

Known platforms that do not support `std::atomic` currently include:
* RPI 2040

## Files
* `atomic`: Extensionless file which will allow `#include <atomic>` to point
to our custom implementation.
* `impl/*.hpp`: Custom (header-only) atomic implementation files.

### Implementation Details

##### Zephyr Spinlock

Designed for Zephyr. Guards atomic calls with a [k_spinlock](https://docs.zephyrproject.org/apidoc/latest/group__spinlock__apis.html#details)
lock/unlock before operations.

### Usage

1) Update the `atomic` (no extension) file to include the desired custom
implementation.

For example for the Zephyr spinlock based implementation `atomic` contains
simply:

```
#include "atomic_zephyr_spinlock.hpp"
```

2) In the project build system CMake file include the directory (`Os/std/atomic`)
which contains the `atomic` file and the implementations so that it is picked
up by the build system BEFORE other system directories.

For example for the [fprime-zephyr-reference project](https://github.com/fprime-community/fprime-zephyr-reference), in
`fprime-zephyr-reference/CMakeLists.txt` we have updated it to include the
following:

```
# Configure custom atomic implementation for RP2040 boards that don't support std::atomic
if(BOARD STREQUAL "rpi_pico")
    message(STATUS "[INFO] Configuring custom atomic implementation for ${BOARD}")

    # Add include directory to override <atomic> header
    include_directories(BEFORE SYSTEM "${CMAKE_CURRENT_LIST_DIR}/lib/fprime/Os/std/atomic")

endif()
```

Note in this example we qualify the `include_directories` for only our desired boards.

3) Re-generate and re-build and use `#include <atomic>` and `std::atomic`.