// ======================================================================
// \title  atomic.hpp
// \author Custom std::atomic Implementation
// \brief  Header for conditionally including custom or standard std::atomic
//
// ======================================================================

#ifndef OS_STD_ATOMIC_HPP
#define OS_STD_ATOMIC_HPP

// STD_ATOMIC_IMPL values:
// 0: Standard library implementation (default)
// 1: Mutex-based custom implementation
// 2: Reserved for future implementation

#if STD_ATOMIC_IMPL == 1
  // Use our mutex-based custom implementation
  #include "Os/std/custom/atomic_mutex.hpp"
  
  // Create an alias to make fprime::atomic appear as std::atomic
  namespace std {
    // This creates an alias so std::atomic<T> will use fprime::atomic<T>
    template<typename T>
    using atomic = os_std_atomic_mutex::atomic<T>;
  }
#elif STD_ATOMIC_IMPL >= 2
  // Reserved for future implementations
  #error "Selected atomic implementation not available yet"
#else
  // Use the standard library implementation
  #include <atomic>
#endif

#endif // OS_STD_ATOMIC_HPP