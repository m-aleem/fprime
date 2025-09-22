// ======================================================================
// \title  Headers.cpp
// \author Rob Bocchino
// \brief  F Prime sequence file headers
//
// \copyright
// Copyright (C) 2009-2018 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.

#include "Svc/CmdSequencer/test/ut/SequenceFiles/FPrime/Headers.hpp"
#include "gtest/gtest.h"

namespace Svc {

namespace SequenceFiles {

namespace FPrime {

namespace Headers {

void serialize(U32 dataSize,
               U32 numRecords,
               FwTimeBaseStoreType timeBase,
               FwTimeContextStoreType timeContext,
               Fw::SerializeBufferBase& destBuffer) {
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, destBuffer.serializeFrom(dataSize));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, destBuffer.serializeFrom(numRecords));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, destBuffer.serializeFrom(timeBase));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, destBuffer.serializeFrom(timeContext));
}

}  // namespace Headers

}  // namespace FPrime

}  // namespace SequenceFiles

}  // namespace Svc
