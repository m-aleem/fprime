#include "Os/std/custom/atomic_mutex.hpp"
#include <iostream>
#include <gtest/gtest.h>

namespace os_std_atomic_test {
    template<typename T>
    using atomic = os_std_atomic_mutex::atomic<T>;
}

// Basic Operations Test
TEST(AtomicTest, BasicOperations) {
    os_std_atomic_test::atomic<int> a(0);
    
    // Test default constructor and load
    EXPECT_EQ(0, a.load()) << "Default constructor should initialize to 0";
    
    // Test store
    a.store(42);
    EXPECT_EQ(42, a.load()) << "store() should set the value to 42";
    
    // Test operator=
    a = 100;
    EXPECT_EQ(100, a.load()) << "operator= should set the value to 100";
    
    // Test implicit conversion
    int val = a;
    EXPECT_EQ(100, val) << "Implicit conversion should return 100";
}

// Exchange Operations Test
TEST(AtomicTest, ExchangeOperations) {
    os_std_atomic_test::atomic<int> a(5);
    
    // Test exchange
    int old = a.exchange(10);
    EXPECT_EQ(5, old) << "exchange() should return old value 5";
    EXPECT_EQ(10, a.load()) << "exchange() should set new value to 10";
    
    // Test compare_exchange_strong success case
    int expected = 10;
    bool success = a.compare_exchange_strong(expected, 15);
    EXPECT_TRUE(success) << "compare_exchange_strong should succeed when expected matches";
    EXPECT_EQ(15, a.load()) << "compare_exchange_strong should set new value to 15";
    
    // Test compare_exchange_strong failure case
    expected = 10; // Incorrect expectation
    success = a.compare_exchange_strong(expected, 20);
    EXPECT_FALSE(success) << "compare_exchange_strong should fail when expected doesn't match";
    EXPECT_EQ(15, a.load()) << "compare_exchange_strong should not change value when it fails";
    EXPECT_EQ(15, expected) << "compare_exchange_strong should update expected to actual value when it fails";
}

// Arithmetic Operations Test
TEST(AtomicTest, ArithmeticOperations) {
    os_std_atomic_test::atomic<int> a(10);
    
    // Test fetch_add
    int old = a.fetch_add(5);
    EXPECT_EQ(10, old) << "fetch_add should return old value 10";
    EXPECT_EQ(15, a.load()) << "fetch_add should increment to 15";
    
    // Test fetch_sub
    old = a.fetch_sub(3);
    EXPECT_EQ(15, old) << "fetch_sub should return old value 15";
    EXPECT_EQ(12, a.load()) << "fetch_sub should decrement to 12";
}

// Increment/Decrement Operators Test
TEST(AtomicTest, IncrementDecrementOperators) {
    os_std_atomic_test::atomic<int> a(5);
    
    // Test pre-increment (++x)
    int val = ++a;
    EXPECT_EQ(6, val) << "Pre-increment (++x) should return new value 6";
    EXPECT_EQ(6, a.load()) << "After pre-increment, value should be 6";
    
    // Test post-increment (x++)
    val = a++;
    EXPECT_EQ(6, val) << "Post-increment (x++) should return old value 6";
    EXPECT_EQ(7, a.load()) << "After post-increment, value should be 7";
    
    // Test pre-decrement (--x)
    val = --a;
    EXPECT_EQ(6, val) << "Pre-decrement (--x) should return new value 6";
    EXPECT_EQ(6, a.load()) << "After pre-decrement, value should be 6";
    
    // Test post-decrement (x--)
    val = a--;
    EXPECT_EQ(6, val) << "Post-decrement (x--) should return old value 6";
    EXPECT_EQ(5, a.load()) << "After post-decrement, value should be 5";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    std::cout << "Testing: os_std_atomic_mutex" << std::endl;
    std::cout << "===============================" << std::endl;

    return RUN_ALL_TESTS();
}