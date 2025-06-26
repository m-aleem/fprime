// ======================================================================
// \title  StateToChoice.cpp
// \author bocchino
// \brief  cpp file for StateToChoice component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/StateToChoice.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

StateToChoice::StateToChoice(const char* const compName)
    : StateToChoiceComponentBase(compName), m_smStateStateToChoice_actionHistory(), m_smStateStateToChoice_guard_g() {}

StateToChoice::~StateToChoice() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void StateToChoice::FppTest_SmState_StateToChoice_action_exitS1(SmId smId,
                                                                FppTest_SmState_StateToChoice::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChoice);
    this->m_smStateStateToChoice_actionHistory.push(signal, ActionId::EXIT_S1);
}

void StateToChoice::FppTest_SmState_StateToChoice_action_exitS2(SmId smId,
                                                                FppTest_SmState_StateToChoice::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChoice);
    this->m_smStateStateToChoice_actionHistory.push(signal, ActionId::EXIT_S2);
}

void StateToChoice::FppTest_SmState_StateToChoice_action_exitS3(SmId smId,
                                                                FppTest_SmState_StateToChoice::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChoice);
    this->m_smStateStateToChoice_actionHistory.push(signal, ActionId::EXIT_S3);
}

void StateToChoice::FppTest_SmState_StateToChoice_action_a(SmId smId, FppTest_SmState_StateToChoice::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChoice);
    this->m_smStateStateToChoice_actionHistory.push(signal, ActionId::A);
}

void StateToChoice::FppTest_SmState_StateToChoice_action_enterS1(SmId smId,
                                                                 FppTest_SmState_StateToChoice::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChoice);
    this->m_smStateStateToChoice_actionHistory.push(signal, ActionId::ENTER_S1);
}

void StateToChoice::FppTest_SmState_StateToChoice_action_enterS2(SmId smId,
                                                                 FppTest_SmState_StateToChoice::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChoice);
    this->m_smStateStateToChoice_actionHistory.push(signal, ActionId::ENTER_S2);
}

void StateToChoice::FppTest_SmState_StateToChoice_action_enterS3(SmId smId,
                                                                 FppTest_SmState_StateToChoice::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChoice);
    this->m_smStateStateToChoice_actionHistory.push(signal, ActionId::ENTER_S3);
}

void StateToChoice::FppTest_SmState_StateToChoice_action_enterS4(SmId smId,
                                                                 FppTest_SmState_StateToChoice::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChoice);
    this->m_smStateStateToChoice_actionHistory.push(signal, ActionId::ENTER_S4);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool StateToChoice ::FppTest_SmState_StateToChoice_guard_g(SmId smId,
                                                           FppTest_SmState_StateToChoice::Signal signal) const {
    FW_ASSERT(smId == SmId::smStateStateToChoice, static_cast<FwAssertArgType>(smId));
    return this->m_smStateStateToChoice_guard_g.call(signal);
}


}  // namespace SmInstanceState

}  // namespace FppTest
