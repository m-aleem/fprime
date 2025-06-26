// ======================================================================
// \title  StateToChild.cpp
// \author bocchino
// \brief  cpp file for StateToChild component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/StateToChild.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

StateToChild::StateToChild(const char* const compName)
    : StateToChildComponentBase(compName), m_smStateStateToChild_actionHistory() {}

StateToChild::~StateToChild() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void StateToChild::FppTest_SmState_StateToChild_action_exitS2(SmId smId, FppTest_SmState_StateToChild::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChild);
    this->m_smStateStateToChild_actionHistory.push(signal, ActionId::EXIT_S2);
}

void StateToChild::FppTest_SmState_StateToChild_action_exitS3(SmId smId, FppTest_SmState_StateToChild::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChild);
    this->m_smStateStateToChild_actionHistory.push(signal, ActionId::EXIT_S3);
}

void StateToChild::FppTest_SmState_StateToChild_action_a(SmId smId, FppTest_SmState_StateToChild::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChild);
    this->m_smStateStateToChild_actionHistory.push(signal, ActionId::A);
}

void StateToChild::FppTest_SmState_StateToChild_action_enterS2(SmId smId, FppTest_SmState_StateToChild::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChild);
    this->m_smStateStateToChild_actionHistory.push(signal, ActionId::ENTER_S2);
}

void StateToChild::FppTest_SmState_StateToChild_action_enterS3(SmId smId, FppTest_SmState_StateToChild::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToChild);
    this->m_smStateStateToChild_actionHistory.push(signal, ActionId::ENTER_S3);
}


}  // namespace SmInstanceState

}  // namespace FppTest
