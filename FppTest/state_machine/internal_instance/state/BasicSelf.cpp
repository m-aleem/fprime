// ======================================================================
// \title  BasicSelf.cpp
// \author bocchino
// \brief  cpp file for BasicSelf component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicSelf.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicSelf::BasicSelf(const char* const compName)
    : BasicSelfComponentBase(compName), m_smStateBasicSelf_action_a_history() {}

BasicSelf::~BasicSelf() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicSelf::FppTest_SmState_BasicSelf_action_a(SmId smId, FppTest_SmState_BasicSelf::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateBasicSelf);
    this->m_smStateBasicSelf_action_a_history.push(signal);
}


}  // namespace SmInstanceState

}  // namespace FppTest
