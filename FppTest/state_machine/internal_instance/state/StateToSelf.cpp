// ======================================================================
// \title  StateToSelf.cpp
// \author bocchino
// \brief  cpp file for StateToSelf component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/StateToSelf.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

StateToSelf::StateToSelf(const char* const compName)
    : StateToSelfComponentBase(compName), m_smStateStateToSelf_actionHistory() {}

StateToSelf::~StateToSelf() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void StateToSelf::FppTest_SmState_StateToSelf_action_exitS1(SmId smId, FppTest_SmState_StateToSelf::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToSelf);
    this->m_smStateStateToSelf_actionHistory.push(signal, ActionId::EXIT_S1);
}

void StateToSelf::FppTest_SmState_StateToSelf_action_exitS2(SmId smId, FppTest_SmState_StateToSelf::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToSelf);
    this->m_smStateStateToSelf_actionHistory.push(signal, ActionId::EXIT_S2);
}

void StateToSelf::FppTest_SmState_StateToSelf_action_exitS3(SmId smId, FppTest_SmState_StateToSelf::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToSelf);
    this->m_smStateStateToSelf_actionHistory.push(signal, ActionId::EXIT_S3);
}

void StateToSelf::FppTest_SmState_StateToSelf_action_a(SmId smId, FppTest_SmState_StateToSelf::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToSelf);
    this->m_smStateStateToSelf_actionHistory.push(signal, ActionId::A);
}

void StateToSelf::FppTest_SmState_StateToSelf_action_enterS1(SmId smId, FppTest_SmState_StateToSelf::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToSelf);
    this->m_smStateStateToSelf_actionHistory.push(signal, ActionId::ENTER_S1);
}

void StateToSelf::FppTest_SmState_StateToSelf_action_enterS2(SmId smId, FppTest_SmState_StateToSelf::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToSelf);
    this->m_smStateStateToSelf_actionHistory.push(signal, ActionId::ENTER_S2);
}

void StateToSelf::FppTest_SmState_StateToSelf_action_enterS3(SmId smId, FppTest_SmState_StateToSelf::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToSelf);
    this->m_smStateStateToSelf_actionHistory.push(signal, ActionId::ENTER_S3);
}


}  // namespace SmInstanceState

}  // namespace FppTest
