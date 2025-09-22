// ======================================================================
// \title  FramingTester.cpp
// \author bocchino
// \brief  cpp file for FramingTester class
// ======================================================================

#include "Svc/FramingProtocol/test/ut/FramingTester.hpp"
#include "STest/Pick/Pick.hpp"
#include "gtest/gtest.h"

namespace Svc {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

FramingTester ::FramingTester(Fw::ComPacketType a_packetType)
    :  // Pick a random data size
      dataSize(STest::Pick::lowerUpper(1, MAX_DATA_SIZE)),
      packetType(a_packetType),
      interface(*this) {
    FW_ASSERT(this->dataSize <= MAX_DATA_SIZE);
    this->fprimeFraming.setup(this->interface);
    // Fill in random data
    for (U32 i = 0; i < sizeof(this->data); ++i) {
        this->data[i] = static_cast<U8>(STest::Pick::lowerUpper(0, 0xFF));
    }
    memset(this->bufferStorage, 0, sizeof this->bufferStorage);
}

// ----------------------------------------------------------------------
// Public member functions
// ----------------------------------------------------------------------

void FramingTester ::check() {
    this->fprimeFraming.frame(this->data, this->dataSize, this->packetType);
    // Check that we received a buffer
    Fw::Buffer* const sentBuffer = this->interface.getSentBuffer();
    ASSERT_NE(sentBuffer, nullptr);
    if (sentBuffer != nullptr) {
        // Check the start word
        this->checkStartWord();
        // Check the packet size
        const U32 packetSize = this->getPacketSize();
        this->checkPacketSize(packetSize);
        // Check the data
        this->checkData();
        // Check the hash value
        this->checkHash(packetSize);
    }
}

// ----------------------------------------------------------------------
// Private member functions
// ----------------------------------------------------------------------

FpFrameHeader::TokenType FramingTester ::getPacketSize() {
    FpFrameHeader::TokenType packetSize = 0;
    Fw::SerialBuffer sb(&this->bufferStorage[PACKET_SIZE_OFFSET], sizeof packetSize);
    sb.fill();
    const Fw::SerializeStatus status = sb.deserializeTo(packetSize);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    return packetSize;
}

void FramingTester ::checkPacketSize(FpFrameHeader::TokenType packetSize) {
    FwSizeType expectedPacketSize = this->dataSize;
    ASSERT_EQ(packetSize, expectedPacketSize);
}

void FramingTester ::checkPacketType() {
    SerialPacketType serialPacketType = 0;
    Fw::SerialBuffer sb(&this->bufferStorage[PACKET_TYPE_OFFSET], sizeof serialPacketType);
    sb.fill();
    const Fw::SerializeStatus status = sb.deserializeTo(serialPacketType);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    typedef Fw::ComPacketType PacketType;
    const PacketType pt = static_cast<PacketType>(serialPacketType);
    ASSERT_EQ(pt, this->packetType);
}

void FramingTester ::checkStartWord() {
    FpFrameHeader::TokenType startWord = 0;
    Fw::SerialBuffer sb(&this->bufferStorage[START_WORD_OFFSET], sizeof startWord);
    sb.fill();
    const Fw::SerializeStatus status = sb.deserializeTo(startWord);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    ASSERT_EQ(startWord, FpFrameHeader::START_WORD);
}

void FramingTester ::checkData() {
    FwSizeType dataOffset = PACKET_TYPE_OFFSET;
    const I32 result = memcmp(this->data, &this->bufferStorage[dataOffset], this->dataSize);
    ASSERT_EQ(result, 0);
}

void FramingTester ::checkHash(FpFrameHeader::TokenType packetSize) {
    Utils::Hash hash;
    Utils::HashBuffer hashBuffer;
    const U32 localDataSize = FpFrameHeader::SIZE + packetSize;
    hash.update(this->bufferStorage, localDataSize);
    hash.final(hashBuffer);
    const U8* const hashAddr = hashBuffer.getBuffAddr();
    const I32 result = memcmp(&this->bufferStorage[localDataSize], hashAddr, HASH_DIGEST_LENGTH);
    ASSERT_EQ(result, 0);
}

}  // namespace Svc
