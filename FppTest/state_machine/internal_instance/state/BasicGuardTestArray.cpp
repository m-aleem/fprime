// ======================================================================
// \title  BasicGuardTestArray.cpp
// \author bocchino
// \brief  cpp file for BasicGuardTestArray component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestArray.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicGuardTestArray::BasicGuardTestArray(const char* const compName)
    : BasicGuardTestArrayComponentBase(compName),
      m_smStateBasicGuardTestArray_action_a_history(),
      m_smStateBasicGuardTestArray_guard_g() {}

BasicGuardTestArray::~BasicGuardTestArray() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicGuardTestArray::FppTest_SmState_BasicGuardTestArray_action_a(
    SmId smId,
    FppTest_SmState_BasicGuardTestArray::Signal signal,
    const SmHarness::TestArray& value) {
    ASSERT_EQ(smId, SmId::smStateBasicGuardTestArray);
    this->m_smStateBasicGuardTestArray_action_a_history.push(signal, value);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool BasicGuardTestArray::FppTest_SmState_BasicGuardTestArray_guard_g(
    SmId smId,
    FppTest_SmState_BasicGuardTestArray::Signal signal,
    const SmHarness::TestArray& value) const {
    FW_ASSERT(smId == SmId::smStateBasicGuardTestArray, static_cast<FwAssertArgType>(smId));
    return this->m_smStateBasicGuardTestArray_guard_g.call(signal, value);
}


}  // namespace SmInstanceState

}  // namespace FppTest
