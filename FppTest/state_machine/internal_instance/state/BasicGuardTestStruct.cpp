// ======================================================================
// \title  BasicGuardTestStruct.cpp
// \author bocchino
// \brief  cpp file for BasicGuardTestStruct component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestStruct.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicGuardTestStruct::BasicGuardTestStruct(const char* const compName)
    : BasicGuardTestStructComponentBase(compName),
      m_smStateBasicGuardTestStruct_action_a_history(),
      m_smStateBasicGuardTestStruct_guard_g() {}

BasicGuardTestStruct::~BasicGuardTestStruct() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicGuardTestStruct::FppTest_SmState_BasicGuardTestStruct_action_a(
    SmId smId,
    FppTest_SmState_BasicGuardTestStruct::Signal signal,
    const SmHarness::TestStruct& value) {
    ASSERT_EQ(smId, SmId::smStateBasicGuardTestStruct);
    this->m_smStateBasicGuardTestStruct_action_a_history.push(signal, value);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool BasicGuardTestStruct::FppTest_SmState_BasicGuardTestStruct_guard_g(
    SmId smId,
    FppTest_SmState_BasicGuardTestStruct::Signal signal,
    const SmHarness::TestStruct& value) const {
    FW_ASSERT(smId == SmId::smStateBasicGuardTestStruct, static_cast<FwAssertArgType>(smId));
    return this->m_smStateBasicGuardTestStruct_guard_g.call(signal, value);
}


}  // namespace SmInstanceState

}  // namespace FppTest
