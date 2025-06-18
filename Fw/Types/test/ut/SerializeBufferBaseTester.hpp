// ======================================================================
// \title  SerializeBufferBaseTester.hpp
// \author m-aleem
// \brief  hpp file for SerializeBufferBaseTester
// ======================================================================

#ifndef FW_SerializeBufferBaseTester_HPP
#define FW_SerializeBufferBaseTester_HPP

#include <Fw/Types/Serializable.hpp>
#include <gtest/gtest.h>


namespace Fw {

class SerializeBufferBaseTester {
  public:
    // Assertion methods for serialization location
    static void assertSerLoc(const Fw::SerializeBufferBase& buff, FwSizeType expected) {
        ASSERT_EQ(expected, buff.m_serLoc);
    }

    static void assertDeserLoc(const Fw::SerializeBufferBase& buff, FwSizeType expected) {
        ASSERT_EQ(expected, buff.m_deserLoc);
    }

    // Reset verification
    static void assertResetState(const Fw::SerializeBufferBase& buff) {
        ASSERT_EQ(0, buff.m_serLoc);
        ASSERT_EQ(0, buff.m_deserLoc);
    }

    // Verify serialization of different data types
    static void verifyU8Serialization(Fw::SerializeBufferBase& buff, U8 value) {
        // Save the current serialization location
        FwSizeType prevSerLoc = buff.m_serLoc;

        // Serialize the value
        Fw::SerializeStatus status = buff.serialize(value);

        // Verify serialization was successful and pointer advanced correctly
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(prevSerLoc + sizeof(U8), buff.m_serLoc);
    }

    static void verifyI8Serialization(Fw::SerializeBufferBase& buff, I8 value) {
        FwSizeType prevSerLoc = buff.m_serLoc;
        Fw::SerializeStatus status = buff.serialize(value);
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(prevSerLoc + sizeof(I8), buff.m_serLoc);
    }

    static void verifyU16Serialization(Fw::SerializeBufferBase& buff, U16 value) {
        FwSizeType prevSerLoc = buff.m_serLoc;
        Fw::SerializeStatus status = buff.serialize(value);
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(prevSerLoc + sizeof(U16), buff.m_serLoc);
    }

    static void verifyI16Serialization(Fw::SerializeBufferBase& buff, I16 value) {
        FwSizeType prevSerLoc = buff.m_serLoc;
        Fw::SerializeStatus status = buff.serialize(value);
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(prevSerLoc + sizeof(I16), buff.m_serLoc);
    }

    static void verifyU32Serialization(Fw::SerializeBufferBase& buff, U32 value) {
        FwSizeType prevSerLoc = buff.m_serLoc;
        Fw::SerializeStatus status = buff.serialize(value);
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(prevSerLoc + sizeof(U32), buff.m_serLoc);
    }

    static void verifyI32Serialization(Fw::SerializeBufferBase& buff, I32 value) {
        FwSizeType prevSerLoc = buff.m_serLoc;
        Fw::SerializeStatus status = buff.serialize(value);
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(prevSerLoc + sizeof(I32), buff.m_serLoc);
    }

    static void verifyU64Serialization(Fw::SerializeBufferBase& buff, U64 value) {
        FwSizeType prevSerLoc = buff.m_serLoc;
        Fw::SerializeStatus status = buff.serialize(value);
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(prevSerLoc + sizeof(U64), buff.m_serLoc);
    }

    static void verifyI64Serialization(Fw::SerializeBufferBase& buff, I64 value) {
        FwSizeType prevSerLoc = buff.m_serLoc;
        Fw::SerializeStatus status = buff.serialize(value);
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(prevSerLoc + sizeof(I64), buff.m_serLoc);
    }

    static void verifyF32Serialization(Fw::SerializeBufferBase& buff, F32 value) {
        FwSizeType prevSerLoc = buff.m_serLoc;
        Fw::SerializeStatus status = buff.serialize(value);
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(prevSerLoc + sizeof(F32), buff.m_serLoc);
    }

    static void verifyF64Serialization(Fw::SerializeBufferBase& buff, F64 value) {
        FwSizeType prevSerLoc = buff.m_serLoc;
        Fw::SerializeStatus status = buff.serialize(value);
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(prevSerLoc + sizeof(F64), buff.m_serLoc);
    }

    // Verify deserialization of different data types
    static void verifyU8Deserialization(Fw::SerializeBufferBase& buff, U8 expectedValue) {
        U8 actualValue;
        FwSizeType prevDeserLoc = buff.m_deserLoc;

        Fw::SerializeStatus status = buff.deserialize(actualValue);

        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(expectedValue, actualValue);
        ASSERT_EQ(prevDeserLoc + sizeof(U8), buff.m_deserLoc);
    }

    static void verifyI8Deserialization(Fw::SerializeBufferBase& buff, I8 expectedValue) {
        I8 actualValue;
        FwSizeType prevDeserLoc = buff.m_deserLoc;

        Fw::SerializeStatus status = buff.deserialize(actualValue);

        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(expectedValue, actualValue);
        ASSERT_EQ(prevDeserLoc + sizeof(I8), buff.m_deserLoc);
    }

    static void verifyU16Deserialization(Fw::SerializeBufferBase& buff, U16 expectedValue) {
        U16 actualValue;
        FwSizeType prevDeserLoc = buff.m_deserLoc;

        Fw::SerializeStatus status = buff.deserialize(actualValue);

        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(expectedValue, actualValue);
        ASSERT_EQ(prevDeserLoc + sizeof(U16), buff.m_deserLoc);
    }

    static void verifyI16Deserialization(Fw::SerializeBufferBase& buff, I16 expectedValue) {
        I16 actualValue;
        FwSizeType prevDeserLoc = buff.m_deserLoc;

        Fw::SerializeStatus status = buff.deserialize(actualValue);

        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(expectedValue, actualValue);
        ASSERT_EQ(prevDeserLoc + sizeof(I16), buff.m_deserLoc);
    }

    static void verifyU32Deserialization(Fw::SerializeBufferBase& buff, U32 expectedValue) {
        U32 actualValue;
        FwSizeType prevDeserLoc = buff.m_deserLoc;

        Fw::SerializeStatus status = buff.deserialize(actualValue);

        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(expectedValue, actualValue);
        ASSERT_EQ(prevDeserLoc + sizeof(U32), buff.m_deserLoc);
    }

    static void verifyI32Deserialization(Fw::SerializeBufferBase& buff, I32 expectedValue) {
        I32 actualValue;
        FwSizeType prevDeserLoc = buff.m_deserLoc;

        Fw::SerializeStatus status = buff.deserialize(actualValue);

        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(expectedValue, actualValue);
        ASSERT_EQ(prevDeserLoc + sizeof(I32), buff.m_deserLoc);
    }

    static void verifyU64Deserialization(Fw::SerializeBufferBase& buff, U64 expectedValue) {
        U64 actualValue;
        FwSizeType prevDeserLoc = buff.m_deserLoc;

        Fw::SerializeStatus status = buff.deserialize(actualValue);

        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(expectedValue, actualValue);
        ASSERT_EQ(prevDeserLoc + sizeof(U64), buff.m_deserLoc);
    }

    static void verifyI64Deserialization(Fw::SerializeBufferBase& buff, I64 expectedValue) {
        I64 actualValue;
        FwSizeType prevDeserLoc = buff.m_deserLoc;

        Fw::SerializeStatus status = buff.deserialize(actualValue);

        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_EQ(expectedValue, actualValue);
        ASSERT_EQ(prevDeserLoc + sizeof(I64), buff.m_deserLoc);
    }

    static void verifyF32Deserialization(Fw::SerializeBufferBase& buff, F32 expectedValue) {
        F32 actualValue;
        FwSizeType prevDeserLoc = buff.m_deserLoc;

        Fw::SerializeStatus status = buff.deserialize(actualValue);

        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_FLOAT_EQ(expectedValue, actualValue);
        ASSERT_EQ(prevDeserLoc + sizeof(F32), buff.m_deserLoc);
    }

    static void verifyF64Deserialization(Fw::SerializeBufferBase& buff, F64 expectedValue) {
        F64 actualValue;
        FwSizeType prevDeserLoc = buff.m_deserLoc;

        Fw::SerializeStatus status = buff.deserialize(actualValue);

        ASSERT_EQ(Fw::FW_SERIALIZE_OK, status);
        ASSERT_DOUBLE_EQ(expectedValue, actualValue);
        ASSERT_EQ(prevDeserLoc + sizeof(F64), buff.m_deserLoc);
    }

    // Verification methods for comparing serialization location
    static void verifySerLocLT(const Fw::SerializeBufferBase& buff, FwSizeType maxValue) {
        ASSERT_LT(buff.m_serLoc, maxValue);
    }

    static void verifySerLocEq(const Fw::SerializeBufferBase& buff, FwSizeType expected) {
        ASSERT_EQ(expected, buff.m_serLoc);
    }

    static void verifyDeserLocEq(const Fw::SerializeBufferBase& buff, FwSizeType expected) {
        ASSERT_EQ(expected, buff.m_deserLoc);
    }
};

}

#endif // FW_SerializeBufferBaseTester_HPP
