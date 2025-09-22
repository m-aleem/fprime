//
// Created by mstarch on 11/13/20.
//
#include <gtest/gtest.h>
#include <Fw/FPrimeBasicTypes.hpp>
#include "Fw/Buffer/Buffer.hpp"
#include "Fw/Types/test/ut/SerializeBufferBaseTester.hpp"

namespace Fw {
class BufferTester {
  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------
    BufferTester() {}

    ~BufferTester() {}

    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------
    void test_basic() {
        U8 data[100];
        U8 faux[100];
        Fw::Buffer buffer;
        // Check basic guarantees
        ASSERT_EQ(buffer.m_context, Fw::Buffer::NO_CONTEXT);
        buffer.setData(data);
        buffer.setSize(sizeof(data));
        buffer.setContext(1234);
        ASSERT_EQ(buffer.getData(), data);
        ASSERT_EQ(buffer.getSize(), sizeof(data));
        ASSERT_EQ(buffer.getContext(), 1234);

        // Test set method is equivalent
        Fw::Buffer buffer_set;
        buffer_set.set(data, sizeof(data), 1234);
        ASSERT_EQ(buffer_set, buffer);

        // Check constructors and assignments
        Fw::Buffer buffer_new(buffer);
        ASSERT_EQ(buffer_new.getData(), data);
        ASSERT_EQ(buffer_new.getSize(), sizeof(data));
        ASSERT_EQ(buffer_new.getContext(), 1234);
        ASSERT_EQ(buffer, buffer_new);

        // Creating empty buffer
        Fw::Buffer testBuffer(nullptr, 0);
        ASSERT_EQ(testBuffer.getData(), nullptr);
        ASSERT_EQ(testBuffer.getSize(), 0);

        // Assignment operator with transitivity
        Fw::Buffer buffer_assignment1, buffer_assignment2;
        ASSERT_NE(buffer_assignment1.getData(), data);
        ASSERT_NE(buffer_assignment1.getSize(), sizeof(data));
        ASSERT_NE(buffer_assignment1.getContext(), 1234);
        ASSERT_NE(buffer_assignment2.getData(), data);
        ASSERT_NE(buffer_assignment2.getSize(), sizeof(data));
        ASSERT_NE(buffer_assignment2.getContext(), 1234);
        buffer_assignment1 = buffer_assignment2 = buffer;
        ASSERT_EQ(buffer_assignment1.getData(), data);
        ASSERT_EQ(buffer_assignment1.getSize(), sizeof(data));
        ASSERT_EQ(buffer_assignment1.getContext(), 1234);
        ASSERT_EQ(buffer_assignment2.getData(), data);
        ASSERT_EQ(buffer_assignment2.getSize(), sizeof(data));
        ASSERT_EQ(buffer_assignment2.getContext(), 1234);

        // Check modifying the copies does not destroy
        buffer_new.setSize(0);
        buffer_new.setData(faux);
        buffer_new.setContext(22222);
        buffer_assignment1.setSize(0);
        buffer_assignment1.setData(faux);
        buffer_assignment1.setContext(22222);
        buffer_assignment2.setSize(0);
        buffer_assignment2.setData(faux);
        buffer_assignment2.setContext(22222);

        ASSERT_EQ(buffer.getData(), data);
        ASSERT_EQ(buffer.getSize(), sizeof(data));
        ASSERT_EQ(buffer.getContext(), 1234);
    }

    void test_representations() {
        U8 data[100];
        Fw::Buffer buffer;
        buffer.setData(data);
        buffer.setSize(sizeof(data));
        buffer.setContext(1234);

        // Test serialization and that it stops before overflowing
        auto serializer = buffer.getSerializer();
        for (U32 i = 0; i < sizeof(data) / 4; i++) {
            ASSERT_EQ(serializer.serializeFrom(i), Fw::FW_SERIALIZE_OK);
        }
        Fw::SerializeStatus stat = serializer.serializeFrom(100);
        ASSERT_NE(stat, Fw::FW_SERIALIZE_OK);

        // And that another call to repr resets it
        serializer.resetSer();
        ASSERT_EQ(serializer.serializeFrom(0), Fw::FW_SERIALIZE_OK);

        // Now deserialize all the things
        auto deserializer = buffer.getDeserializer();
        U32 out;
        for (U32 i = 0; i < sizeof(data) / 4; i++) {
            ASSERT_EQ(deserializer.deserializeTo(out), Fw::FW_SERIALIZE_OK);
            ASSERT_EQ(i, out);
        }
        ASSERT_NE(deserializer.deserializeTo(out), Fw::FW_SERIALIZE_OK);
        deserializer.setBuffLen(buffer.getSize());
        ASSERT_EQ(deserializer.deserializeTo(out), Fw::FW_SERIALIZE_OK);
        ASSERT_EQ(0, out);
    }

    void test_serialization() {
        U8 data[100];
        U8 wire[100];

        Fw::Buffer buffer;
        buffer.setData(data);
        buffer.setSize(sizeof(data));
        buffer.setContext(1234);

        Fw::ExternalSerializeBuffer externalSerializeBuffer(wire, sizeof(wire));
        externalSerializeBuffer.serializeFrom(buffer);
        Fw::SerializeBufferBaseTester::verifySerLocLT(externalSerializeBuffer, sizeof(data));

        Fw::Buffer buffer_new;
        externalSerializeBuffer.deserializeTo(buffer_new);
        ASSERT_EQ(buffer_new, buffer);
    }
};
}  // namespace Fw

TEST(Nominal, BasicBuffer) {
    Fw::BufferTester tester;
    tester.test_basic();
}

TEST(Nominal, Representations) {
    Fw::BufferTester tester;
    tester.test_representations();
}

TEST(Nominal, Serialization) {
    Fw::BufferTester tester;
    tester.test_serialization();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
