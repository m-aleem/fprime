# F-Prime Standard Library Extensions (Os/std)

This module provides custom implementations of C++ standard library components for the F-Prime framework. These implementations serve as drop-in replacements for environments where the standard library implementation is not available, has limitations, or needs to be customized for specific use cases.

## Table of Contents

- [Overview](#overview)
- [Components](#components)
  - [std::atomic](#stdatomic)
    - [Files](#available-files)
    - [Usage](#usage)
    - [Configuration](#configuration)
    - [Implementation Details](#implementation-details)

## Overview

The F-Prime Standard Library Extensions (Os/std) provide alternative implementations of C++ standard library components, allowing F-Prime to be deployed in environments with limited standard library support or where specific implementation details need to be controlled.

## Components

### std::atomic

The `std::atomic` implementation provides atomic operations for data types. Multiple implementations are available:

#### Files

- `atomic.hpp` - Main header that conditionally includes the selected `std::atomic` implementation
- `custom/atomic_mutex.hpp`: A mutex-based implementation of atomic operations


#### Usage

Including `std::atomic`:

```cpp
#include "Os/std/atomic.hpp"
```

The appropriate implementation will be selected based on your configuration.

Usage follows the `std::atomic` interface (see [C++ Reference std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic.html) for details):

```cpp
std::atomic<int> counter(0);
counter.store(5);
int value = counter.load();
```

#### Configuration

The `std::atomic` implementation can be configured via CMake:

- **STD_ATOMIC_IMPL**: Selects which implementation to use:
  - `0`: Standard library implementation (default)
  - `1`: Mutex-based custom implementation 
  - `2+`: Reserved for future implementations (e.g., ISR-safe implementation)

**WARNING**: At the time of writing, attempting to use option 1 when 0 is selected will result in a compile error.

#### Implementation Details

##### Standard Library Implementation (0)

Uses the standard C++ library `std::atomic` implementation, which typically uses hardware atomic instructions for optimal performance.

##### Mutex-based Implementation (1)

The custom mutex-based implementation provides the core functionality of `std::atomic`:

- Basic operations: `load()`, `store()`, `exchange()`
- Compare-and-exchange: `compare_exchange_weak()`, `compare_exchange_strong()`
- Arithmetic operations: `fetch_add()`, `fetch_sub()`
- Increment/decrement operators: `++`, `--` (both prefix and postfix)

###### Limitations

- **Not ISR-Safe**: The mutex-based implementation is not safe for use in Interrupt Service Routines (ISRs) since mutexes can block and ISRs cannot wait.
- **Performance**: Mutex-based atomics are generally slower than hardware-based atomics available in the standard library.
- **Memory Ordering**: The custom implementation does not implement memory ordering as specified in the C++ standard.
