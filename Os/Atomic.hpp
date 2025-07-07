// ======================================================================
// \title  Atomic.hpp
// \brief  OSAL interface for atomic operations
// ======================================================================
/**
 * @file
 * @brief OSAL Atomic Operations Interface
 *
 * This file provides an Operating System Abstraction Layer (OSAL) for atomic operations.
 * 
 * BACKGROUND:
 * F Prime currently uses std::atomic for atomic operations, but std::atomic is not supported
 * on all platforms (such as Atmel ATMega and ARM Cortex 6M (PICO 1) boards).
 *
 * PURPOSE:
 * This interface provides a consistent API for atomic operations that can be implemented
 * differently depending on the platform's capabilities:
 * 1. On platforms that support std::atomic, it uses std::atomic as the underlying implementation
 * 2. On platforms without std::atomic support, alternative implementations can be done
 *
 * USAGE:
 * Use Os::AtomicBool, Os::AtomicU32, etc. instead of std::atomic<bool>, std::atomic<U32>, etc.
 * 
 * @note This is a header-only implementation to allow for template specialization
 */

#ifndef OS_ATOMIC_HPP
#define OS_ATOMIC_HPP

#include "Fw/Types/BasicTypes.hpp"
#include <atomic>

namespace Os {

/**
 * @brief Memory order options for atomic operations
 * 
 * This enum abstracts memory ordering constraints from the underlying implementation.
 * By providing our own memory order enum rather than directly using std::memory_order:
 * 1. We maintain platform independence (important for platforms without std::atomic)
 * 2. We abstract implementation details from users of the OSAL interface
 * 3. We ensure API stability if underlying memory ordering semantics change
 */
enum class AtomicMemoryOrder {
    RELAXED,  // No synchronization
    ACQUIRE,  // Acquire memory barrier
    RELEASE,  // Release memory barrier
    ACQ_REL,  // Acquire+Release barrier
    SEQ_CST   // Sequentially consistent (default)
};

/**
 * @brief Convert OS memory order to std::memory_order
 * 
 * @param order OS memory order
 * @return Equivalent std::memory_order
 */
inline std::memory_order convertToStdMemoryOrder(AtomicMemoryOrder order) {
    switch (order) {
        case AtomicMemoryOrder::RELAXED: return std::memory_order_relaxed;
        case AtomicMemoryOrder::ACQUIRE: return std::memory_order_acquire;
        case AtomicMemoryOrder::RELEASE: return std::memory_order_release;
        case AtomicMemoryOrder::ACQ_REL: return std::memory_order_acq_rel;
        case AtomicMemoryOrder::SEQ_CST:
        default:                         return std::memory_order_seq_cst;
    }
}

/**
 * @brief Template class for atomic operations
 * 
 * This class provides a platform-independent interface for atomic operations.
 * It wraps std::atomic on platforms that support it.
 */
template<typename T>
class Atomic {  
    private:
        std::atomic<T> m_atomic; // Underlying std::atomic implementation

    public:
        /**
        * @brief Default constructor
        */
        Atomic() : m_atomic() {}

        /**
        * @brief Constructor with initial value
        * 
        * @param initial_value Initial value for the atomic variable
        */
        explicit Atomic(T initial_value) : m_atomic(initial_value) {}
        
        /**
        * @brief No copy or move allowed
        */
        Atomic(const Atomic&) = delete;
        Atomic& operator=(const Atomic&) = delete;
        
        /**
        * @brief Load the current value
        * 
        * @param order Memory ordering constraint
        * @return Current value
        */
        T load(AtomicMemoryOrder order = AtomicMemoryOrder::SEQ_CST) const {
            return m_atomic.load(convertToStdMemoryOrder(order));
        }
        
        /**
        * @brief Store a new value
        * 
        * @param desired New value to store
        * @param order Memory ordering constraint
        */
        void store(T desired, AtomicMemoryOrder order = AtomicMemoryOrder::SEQ_CST) {
            m_atomic.store(desired, convertToStdMemoryOrder(order));
        }
        
        /**
        * @brief Assignment operator = to store a new value
        * 
        * @param desired New value to store
        * @return The stored value
        */
        T operator=(T desired) {
            m_atomic.store(desired);
            return desired;
        }
        
        /**
        * @brief Exchange the current value with a new one
        * 
        * @param desired New value to store
        * @param order Memory ordering constraint
        * @return Previous value
        */
        T exchange(T desired, AtomicMemoryOrder order = AtomicMemoryOrder::SEQ_CST) {
            return m_atomic.exchange(desired, convertToStdMemoryOrder(order));
        }
        
        /**
        * @brief Compare and exchange (strong version)
        * 
        * @param expected Expected current value (will be updated if comparison fails)
        * @param desired New value to store if comparison succeeds
        * @param success Memory ordering on success
        * @param failure Memory ordering on failure
        * @return True if exchange occurred, false otherwise
        */
        bool compare_exchange_strong(T& expected, T desired, 
                                    AtomicMemoryOrder success = AtomicMemoryOrder::SEQ_CST,
                                    AtomicMemoryOrder failure = AtomicMemoryOrder::SEQ_CST) {
            return m_atomic.compare_exchange_strong(
                expected,
                desired,
                convertToStdMemoryOrder(success),
                convertToStdMemoryOrder(failure)
            );
        }
        
        /**
        * @brief Add to the current value and return previous value
        * 
        * @param arg Value to add
        * @param order Memory ordering constraint
        * @return Previous value before addition
        */
        T fetch_add(T arg, AtomicMemoryOrder order = AtomicMemoryOrder::SEQ_CST) {
            return m_atomic.fetch_add(arg, convertToStdMemoryOrder(order));
        }
        
        /**
        * @brief Subtract from the current value and return previous value
        * 
        * @param arg Value to subtract
        * @param order Memory ordering constraint
        * @return Previous value before subtraction
        */
        T fetch_sub(T arg, AtomicMemoryOrder order = AtomicMemoryOrder::SEQ_CST) {
            return m_atomic.fetch_sub(arg, convertToStdMemoryOrder(order));
        }
        
        /**
        * @brief Prefix increment operator
        * 
        * @return New value after increment
        */
        T operator++() {
            return m_atomic.fetch_add(1) + 1;
        }
        
        /**
        * @brief Postfix increment operator
        * 
        * @return Value before increment
        */
        T operator++(int) {
            return m_atomic.fetch_add(1);
        }
        
        /**
        * @brief Prefix decrement operator
        * 
        * @return New value after decrement
        */
        T operator--() {
            return m_atomic.fetch_sub(1) - 1;
        }
        
        /**
        * @brief Postfix decrement operator
        * 
        * @return Value before decrement
        */
        T operator--(int) {
            return m_atomic.fetch_sub(1);
        }
        
        /**
        * @brief Implicit conversion to underlying type
        * 
        * This allows atomic variables to be used in expressions as if they
        * were their underlying type, for compatibility with existing code.
        * 
        * @return Current value
        */
        operator T() const {
            return m_atomic.load();
        }

};

/**
 * @brief Boolean specialization
 * 
 * Specialization of Atomic class for boolean values, omitting
 * operations that don't make sense for bools.
 */
template<>
class Atomic<bool> {
    private:
        std::atomic<bool> m_atomic; // Underlying std::atomic implementation
    public:
        /**
        * @brief Default constructor. Initializes to false.
        */
        Atomic() : m_atomic(false) {}

        /**
        * @brief Constructor with initial value
        * 
        * @param initial_value Initial value for the atomic boolean
        */
        explicit Atomic(bool initial_value) : m_atomic(initial_value) {}
        
        /**
        * @brief No copy or move allowed
        */
        Atomic(const Atomic&) = delete;
        Atomic& operator=(const Atomic&) = delete;
        
        /**
        * @brief Load the current value
        * 
        * @param order Memory ordering constraint
        * @return Current value
        */
        bool load(AtomicMemoryOrder order = AtomicMemoryOrder::SEQ_CST) const {
            return m_atomic.load(convertToStdMemoryOrder(order));
        }
        
        /**
        * @brief Store a new value
        * 
        * @param desired New value to store
        * @param order Memory ordering constraint
        */
        void store(bool desired, AtomicMemoryOrder order = AtomicMemoryOrder::SEQ_CST) {
            m_atomic.store(desired, convertToStdMemoryOrder(order));
        }
        
        /**
        * @brief Assignment operator - store a new value
        * 
        * @param desired New value to store
        * @return The stored value
        */
        bool operator=(bool desired) {
            m_atomic.store(desired);
            return desired;
        }
        
        /**
        * @brief Exchange the current value with a new one
        * 
        * @param desired New value to store
        * @param order Memory ordering constraint
        * @return Previous value
        */
        bool exchange(bool desired, AtomicMemoryOrder order = AtomicMemoryOrder::SEQ_CST) {
            return m_atomic.exchange(desired, convertToStdMemoryOrder(order));
        }
        
        /**
        * @brief Compare and exchange (strong version)
        * 
        * @param expected Expected current value (will be updated if comparison fails)
        * @param desired New value to store if comparison succeeds
        * @param success Memory ordering on success
        * @param failure Memory ordering on failure
        * @return True if exchange occurred, false otherwise
        */
        bool compare_exchange_strong(bool& expected, bool desired, 
                                    AtomicMemoryOrder success = AtomicMemoryOrder::SEQ_CST,
                                    AtomicMemoryOrder failure = AtomicMemoryOrder::SEQ_CST) {
            return m_atomic.compare_exchange_strong(
                expected,
                desired,
                convertToStdMemoryOrder(success),
                convertToStdMemoryOrder(failure)
            );
        }
        
        /**
        * @brief Implicit conversion to bool
        * 
        * This allows atomic booleans to be used in expressions as if they
        * were regular bools, for compatibility with existing code.
        * 
        * @return Current value
        */
        operator bool() const {
            return m_atomic.load();
        }

};

// Type aliases for common atomic types
using AtomicBool = Atomic<bool>;
using AtomicU8 = Atomic<U8>;
using AtomicI8 = Atomic<I8>;
using AtomicU16 = Atomic<U16>;
using AtomicI16 = Atomic<I16>;
using AtomicU32 = Atomic<U32>;
using AtomicI32 = Atomic<I32>;
using AtomicU64 = Atomic<U64>;
using AtomicI64 = Atomic<I64>;
using AtomicF32 = Atomic<F32>;
using AtomicF64 = Atomic<F64>;

} // namespace Os

#endif // OS_ATOMIC_HPP
