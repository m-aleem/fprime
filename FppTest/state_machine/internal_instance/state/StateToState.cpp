// ======================================================================
// \title  StateToState.cpp
// \author bocchino
// \brief  cpp file for StateToState component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/StateToState.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

StateToState::StateToState(const char* const compName)
    : StateToStateComponentBase(compName), m_smStateStateToState_actionHistory() {}

StateToState::~StateToState() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void StateToState::FppTest_SmState_StateToState_action_exitS1(SmId smId, FppTest_SmState_StateToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToState);
    this->m_smStateStateToState_actionHistory.push(signal, ActionId::EXIT_S1);
}

void StateToState::FppTest_SmState_StateToState_action_exitS2(SmId smId, FppTest_SmState_StateToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToState);
    this->m_smStateStateToState_actionHistory.push(signal, ActionId::EXIT_S2);
}

void StateToState::FppTest_SmState_StateToState_action_exitS3(SmId smId, FppTest_SmState_StateToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToState);
    this->m_smStateStateToState_actionHistory.push(signal, ActionId::EXIT_S3);
}

void StateToState::FppTest_SmState_StateToState_action_a(SmId smId, FppTest_SmState_StateToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToState);
    this->m_smStateStateToState_actionHistory.push(signal, ActionId::A);
}

void StateToState::FppTest_SmState_StateToState_action_enterS1(SmId smId, FppTest_SmState_StateToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToState);
    this->m_smStateStateToState_actionHistory.push(signal, ActionId::ENTER_S1);
}

void StateToState::FppTest_SmState_StateToState_action_enterS2(SmId smId, FppTest_SmState_StateToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToState);
    this->m_smStateStateToState_actionHistory.push(signal, ActionId::ENTER_S2);
}

void StateToState::FppTest_SmState_StateToState_action_enterS3(SmId smId, FppTest_SmState_StateToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToState);
    this->m_smStateStateToState_actionHistory.push(signal, ActionId::ENTER_S3);
}

void StateToState::FppTest_SmState_StateToState_action_enterS4(SmId smId, FppTest_SmState_StateToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToState);
    this->m_smStateStateToState_actionHistory.push(signal, ActionId::ENTER_S4);
}

void StateToState::FppTest_SmState_StateToState_action_enterS5(SmId smId, FppTest_SmState_StateToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToState);
    this->m_smStateStateToState_actionHistory.push(signal, ActionId::ENTER_S5);
}


}  // namespace SmInstanceState

}  // namespace FppTest
