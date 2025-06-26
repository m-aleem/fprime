// ======================================================================
// \title  BasicGuardTestAbsType.cpp
// \author bocchino
// \brief  cpp file for BasicGuardTestAbsType component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestAbsType.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicGuardTestAbsType::BasicGuardTestAbsType(const char* const compName)
    : BasicGuardTestAbsTypeComponentBase(compName),
      m_value(),
      m_smStateBasicGuardTestAbsType_action_a_history(),
      m_smStateBasicGuardTestAbsType_guard_g() {}

BasicGuardTestAbsType::~BasicGuardTestAbsType() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicGuardTestAbsType::FppTest_SmState_BasicGuardTestAbsType_action_a(
    SmId smId,
    FppTest_SmState_BasicGuardTestAbsType::Signal signal,
    const SmHarness::TestAbsType& value) {
    ASSERT_EQ(smId, SmId::smStateBasicGuardTestAbsType);
    this->m_smStateBasicGuardTestAbsType_action_a_history.push(signal, value);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool BasicGuardTestAbsType::FppTest_SmState_BasicGuardTestAbsType_guard_g(
    SmId smId,
    FppTest_SmState_BasicGuardTestAbsType::Signal signal,
    const SmHarness::TestAbsType& value) const {
    FW_ASSERT(smId == SmId::smStateBasicGuardTestAbsType, static_cast<FwAssertArgType>(smId));
    return this->m_smStateBasicGuardTestAbsType_guard_g.call(signal, value);
}

// ----------------------------------------------------------------------
// Overflow hook implementations for internal state machines
// ----------------------------------------------------------------------

void BasicGuardTestAbsType::smStateBasicGuardTestAbsType_stateMachineOverflowHook(SmId smId,
                                                                                  FwEnumStoreType signal,
                                                                                  Fw::SerializeBufferBase& buffer) {
    this->m_hookCalled = true;
    ASSERT_EQ(smId, SmId::smStateBasicGuardTestAbsType);
    ASSERT_EQ(static_cast<SmState_BasicGuardTestAbsType::Signal>(signal), SmState_BasicGuardTestAbsType::Signal::s);
    SmHarness::TestAbsType value;
    const auto status = buffer.deserialize(value);
    ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
    ASSERT_EQ(buffer.getBuffLeft(), 0);
    ASSERT_EQ(value, this->m_value);
}


}  // namespace SmInstanceState

}  // namespace FppTest
