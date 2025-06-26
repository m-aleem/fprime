// ======================================================================
// \title  BasicGuardString.cpp
// \author bocchino
// \brief  cpp file for BasicGuardString component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/state/FppConstantsAc.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardString.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicGuardString ::BasicGuardString(const char* const compName)
    : BasicGuardStringComponentBase(compName),
      m_smStateBasicGuardString_action_a_history(),
      m_smStateBasicGuardString_guard_g() {}

BasicGuardString ::~BasicGuardString() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicGuardString ::FppTest_SmState_BasicGuardString_action_a(SmId smId,
                                                                  FppTest_SmState_BasicGuardString::Signal signal,
                                                                  const Fw::StringBase& value) {
    ASSERT_EQ(smId, SmId::smStateBasicGuardString);
    this->m_smStateBasicGuardString_action_a_history.push(signal, Fw::String(value));
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool BasicGuardString ::FppTest_SmState_BasicGuardString_guard_g(SmId smId,
                                                                 FppTest_SmState_BasicGuardString::Signal signal,
                                                                 const Fw::StringBase& value) const {
    FW_ASSERT(smId == SmId::smStateBasicGuardString, static_cast<FwAssertArgType>(smId));
    return this->m_smStateBasicGuardString_guard_g.call(signal, Fw::String(value));
}



}  // namespace SmInstanceState

}  // namespace FppTest
