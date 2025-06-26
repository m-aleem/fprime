// ======================================================================
// \title  BasicGuard.cpp
// \author bocchino
// \brief  cpp file for BasicGuard component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicGuard.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicGuard ::BasicGuard(const char* const compName)
    : BasicGuardComponentBase(compName), m_smStateBasicGuard_action_a_history(), m_smStateBasicGuard_guard_g() {}

BasicGuard ::~BasicGuard() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicGuard ::FppTest_SmState_BasicGuard_action_a(SmId smId, FppTest_SmState_BasicGuard::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateBasicGuard);
    this->m_smStateBasicGuard_action_a_history.push(signal);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool BasicGuard ::FppTest_SmState_BasicGuard_guard_g(SmId smId, FppTest_SmState_BasicGuard::Signal signal) const {
    FW_ASSERT(smId == SmId::smStateBasicGuard, static_cast<FwAssertArgType>(smId));
    return this->m_smStateBasicGuard_guard_g.call(signal);
}



// ----------------------------------------------------------------------
// Helper functions
// ----------------------------------------------------------------------

void BasicGuard::checkActionsAndGuards(FwIndexType expectedActionSize, FwIndexType expectedGuardSize) {
    ASSERT_EQ(this->m_smStateBasicGuard_action_a_history.getSize(), expectedActionSize);
    for (FwIndexType i = 0; i < expectedActionSize; i++) {
        ASSERT_EQ(this->m_smStateBasicGuard_action_a_history.getItemAt(i), SmState_BasicGuard::Signal::s);
    }
    ASSERT_EQ(this->m_smStateBasicGuard_guard_g.getCallHistory().getSize(), expectedGuardSize);
    for (FwIndexType i = 0; i < expectedGuardSize; i++) {
        ASSERT_EQ(this->m_smStateBasicGuard_guard_g.getCallHistory().getItemAt(i), SmState_BasicGuard::Signal::s);
    }
}

}  // namespace SmInstanceState

}  // namespace FppTest
