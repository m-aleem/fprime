// ======================================================================
// \title  atomic_mutex.hpp
// \brief  Custom implementation of std::atomic for F Prime
//
// ======================================================================

#include <Fw/Types/BasicTypes.hpp>
#include <mutex>

namespace os_std_atomic_mutex {

// Memory order enum to match std::memory_order
enum memory_order {
    memory_order_relaxed,
    memory_order_consume,
    memory_order_acquire,
    memory_order_release,
    memory_order_acq_rel,
    memory_order_seq_cst
};


/**
 * Custom implementation of std::atomic that mimics the standard library interface
 * but can be used in environments where the standard library is not available
 * or when a custom implementation is preferred.
 */
template<typename T>
class atomic {
private:
    // The actual value storage
    T m_value;
    
    // Mutex to protect access to the value
    mutable std::mutex m_mutex;
    
  public:
    /**
     * Default constructor
     */
    atomic() noexcept : m_value() {}

    /**
     * Constructor with initial value
     */
    constexpr atomic(T desired) noexcept : m_value(desired) {}

    /**
     * Copy constructor is deleted
     */
    atomic(const atomic&) = delete;

    /**
     * Assignment operator is deleted
     */
    atomic& operator=(const atomic&) = delete;

    /**
     * Assignment operator from T
     */
    T operator=(T desired) noexcept {
        store(desired);
        return desired;
    }

    /**
     * Loads the current value
     */
    T load(memory_order order = memory_order_seq_cst) const noexcept {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_value;
    }

    /**
     * Stores a new value
     */
    void store(T desired, memory_order order = memory_order_seq_cst) noexcept {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_value = desired;
    }

    /**
     * Exchanges the stored value with the given value
     */
    T exchange(T desired, memory_order order = memory_order_seq_cst) noexcept {
        std::lock_guard<std::mutex> lock(m_mutex);
        T old = m_value;
        m_value = desired;
        return old;
    }

    /**
     * Compares the stored value with expected and replaces with desired if equal
     */
    bool compare_exchange_weak(T& expected, T desired,
                              memory_order success = memory_order_seq_cst,
                              memory_order failure = memory_order_seq_cst) noexcept {
        std::lock_guard<std::mutex> lock(m_mutex);
        
        if (m_value == expected) {
            m_value = desired;
            return true;
        } else {
            expected = m_value;
            return false;
        }
    }

    /**
     * Compares the stored value with expected and replaces with desired if equal
     */
    bool compare_exchange_strong(T& expected, T desired,
                                memory_order success = memory_order_seq_cst,
                                memory_order failure = memory_order_seq_cst) noexcept {
        // Use compare_exchange_weak implementation, protected by the same mutex
        return compare_exchange_weak(expected, desired, success, failure);
    }

    /**
     * Implicit conversion to T
     */
    operator T() const noexcept {
        return load();
    }

    /**
     * Fetch and add operation
     */
    T fetch_add(T arg, memory_order order = memory_order_seq_cst) noexcept {
        std::lock_guard<std::mutex> lock(m_mutex);
        T old = m_value;
        m_value += arg;
        return old;
    }

    /**
     * Fetch and subtract operation
     */
    T fetch_sub(T arg, memory_order order = memory_order_seq_cst) noexcept {
        std::lock_guard<std::mutex> lock(m_mutex);
        T old = m_value;
        m_value -= arg;
        return old;
    }

    /**
     * Pre-increment operator (++x)
     * Returns the new value
     */
    T operator++() noexcept {
        // Use fetch_add and add 1 to return the new value
        return fetch_add(1) + 1;
    }

    /**
     * Post-increment operator (x++)
     * Returns the old value
     */
    T operator++(int) noexcept {
        // fetch_add already returns the old value
        return fetch_add(1);
    }

    /**
     * Pre-decrement operator (--x)
     * Returns the new value
     */
    T operator--() noexcept {
        // Use fetch_sub and subtract 1 to return the new value
        return fetch_sub(1) - 1;
    }

    /**
     * Post-decrement operator (x--)
     * Returns the old value
     */
    T operator--(int) noexcept {
        // fetch_sub already returns the old value
        return fetch_sub(1);
    }
};

} // namespace fprime
