// ======================================================================
// \title  PrimitiveStructTest.cpp
// \author T. Chieu
// \brief  cpp file for PrimitiveStructTest class
//
// \copyright
// Copyright (C) 2009-2022 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include "FppTest/struct/PrimitiveSerializableAc.hpp"
#include "FppTest/utils/Utils.hpp"

#include "Fw/Types/SerialBuffer.hpp"
#include "Fw/Types/StringUtils.hpp"
#include "STest/Pick/Pick.hpp"

#include "gtest/gtest.h"

#include <sstream>

// Test Primitive struct class
class PrimitiveStructTest : public ::testing::Test {
protected:
    void SetUp() override {
        testBool = true;
        testU32 = FppTest::Utils::getNonzeroU32();
        testI16 = static_cast<I16>(FppTest::Utils::getNonzeroU32());
        testF64 = static_cast<F64>(FppTest::Utils::getNonzeroU32());
    }

    void assertStructMembers(const Primitive& s) {
        ASSERT_EQ(s.get_mBool(), testBool);
        ASSERT_EQ(s.get_mU32(), testU32);
        ASSERT_EQ(s.get_mI16(), testI16);
        ASSERT_EQ(s.get_mF64(), testF64);
    }

    void assertUnsuccessfulSerialization(Primitive& s, U32 bufSize) {
        // Avoid creating an array of size zero
        U8 data[bufSize + 1];
        Fw::SerialBuffer buf(data, bufSize);
        Fw::SerializeStatus status;

        // Serialize
        status = buf.serialize(s);
        ASSERT_NE(status, Fw::FW_SERIALIZE_OK);

        // Deserialize
        status = buf.deserialize(s);
        ASSERT_NE(status, Fw::FW_SERIALIZE_OK);
    }

    bool testBool;
    U32 testU32;
    I16 testI16;
    F64 testF64;
};

// Test struct constants and default constructor
TEST_F(PrimitiveStructTest, Default) {
    Primitive s;

    // Constants
    ASSERT_EQ(
        Primitive::SERIALIZED_SIZE,
        sizeof(U8) 
            + sizeof(U32) 
            + sizeof(I16) 
            + sizeof(F64) 
    );

    // Default constructor
    ASSERT_EQ(s.get_mBool(), false);
    ASSERT_EQ(s.get_mU32(), 0);
    ASSERT_EQ(s.get_mI16(), 0);
    ASSERT_EQ(s.get_mF64(), 0.0);
}

// Test struct constructors
TEST_F(PrimitiveStructTest, Constructors) {
    // Member constructor
    Primitive s1(testBool, testU32, testI16, testF64);
    assertStructMembers(s1);

    // Copy constructor
    Primitive s2(s1);
    assertStructMembers(s2);
}

// Test struct assignment operator
TEST_F(PrimitiveStructTest, AssignmentOp) {
    Primitive s1;
    Primitive s2(testBool, testU32, testI16, testF64);

    // Copy assignment
    s1 = s2;
    assertStructMembers(s1);

    Primitive& s1Ref = s1;
    s1 = s1Ref;
    ASSERT_EQ(&s1, &s1Ref);
}

// Test struct equality and inequality operators
TEST_F(PrimitiveStructTest, EqualityOp) {
    Primitive s1, s2;

    ASSERT_TRUE(s1 == s2);
    ASSERT_FALSE(s1 != s2);

    s1.set_mBool(testBool);

    ASSERT_FALSE(s1 == s2);
    ASSERT_TRUE(s1 != s2);

    s2.set_mBool(testBool);
    s1.set_mU32(testU32);

    ASSERT_FALSE(s1 == s2);
    ASSERT_TRUE(s1 != s2);

    s2.set_mU32(testU32);
    s1.set_mI16(testI16);

    ASSERT_FALSE(s1 == s2);
    ASSERT_TRUE(s1 != s2);

    s2.set_mI16(testI16);
    s1.set_mF64(testF64);

    ASSERT_FALSE(s1 == s2);
    ASSERT_TRUE(s1 != s2);

    s2.set_mF64(testF64);

    ASSERT_TRUE(s1 == s2);
    ASSERT_FALSE(s1 != s2);
}

// Test struct getter and setter functions
TEST_F(PrimitiveStructTest, GetterSetterFunctions) {
    Primitive s1, s2;

    // Set all members
    s1.set(testBool, testU32, testI16, testF64);
    assertStructMembers(s1);

    // Set individual members
    s2.set_mBool(testBool);
    ASSERT_EQ(s2.get_mBool(), testBool);

    s2.set_mU32(testU32);
    ASSERT_EQ(s2.get_mU32(), testU32);

    s2.set_mI16(testI16);
    ASSERT_EQ(s2.get_mI16(), testI16);

    s2.set_mF64(testF64);
    ASSERT_EQ(s2.get_mF64(), testF64);
}

// Test struct serialization and deserialization
TEST_F(PrimitiveStructTest, Serialization) {
    Primitive s(testBool, testU32, testI16, testF64);
    Primitive sCopy;

    Fw::SerializeStatus status;

    // Test successful serialization
    U8 data[Primitive::SERIALIZED_SIZE];
    Fw::SerialBuffer buf(data, sizeof(data));

    // Serialize
    status = buf.serialize(s);

    ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
    ASSERT_EQ(buf.getBuffLength(), Primitive::SERIALIZED_SIZE);

    // Deserialize
    status = buf.deserialize(sCopy);

    ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
    ASSERT_EQ(s, sCopy);

    // Test unsuccessful serialization
    assertUnsuccessfulSerialization(s, sizeof(U8) - 1);
    assertUnsuccessfulSerialization(s, sizeof(U8) + sizeof(U32) - 1);
    assertUnsuccessfulSerialization(s, sizeof(U8) + sizeof(U32) 
                                       + sizeof(I16) - 1);
    assertUnsuccessfulSerialization(s, Primitive::SERIALIZED_SIZE - 1);
}

// Test struct toString() and ostream operator functions
TEST_F(PrimitiveStructTest, ToString) {
    Primitive s(testBool, testU32, testI16, testF64);
    std::stringstream buf1, buf2;

    buf1 << s;

    buf2 << "( "
         << "mBool = " << testBool << ", "       
         << "mU32 = " << testU32 << ", "
         << "mI16 = " << testI16 << ", "        
         << "mF64 = " << std::fixed << testF64        
         << " )";

    ASSERT_STREQ(buf1.str().c_str(), buf2.str().c_str());
}
