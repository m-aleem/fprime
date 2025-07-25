// ======================================================================
// \title  Fw/FilePacket/GTest/DataPacket.cpp
// \author bocchino
// \brief  Test utilities for data file packets
//
// \copyright
// Copyright (C) 2016, California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <Fw/FilePacket/GTest/FilePackets.hpp>
#include <Fw/Types/GTest/Bytes.hpp>

namespace Fw {

  namespace GTest {

    void FilePackets::DataPacket ::
      compare(
          const FilePacket::DataPacket& expected,
          const FilePacket::DataPacket& actual
      )
    {
      FilePackets::Header::compare(expected.asHeader(), actual.asHeader());
      ASSERT_EQ(expected.getByteOffset(), actual.getByteOffset());
      Bytes expectedData(expected.getData(), expected.getDataSize());
      Bytes actualData(actual.getData(), actual.getDataSize());
      Bytes::compare(expectedData, actualData);
    }

  }

}
