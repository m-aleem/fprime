// ======================================================================
// \title  BasicTestAbsType.cpp
// \author bocchino
// \brief  cpp file for BasicTestAbsType component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicTestAbsType.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicTestAbsType ::BasicTestAbsType(const char* const compName)
    : BasicTestAbsTypeComponentBase(compName),
      m_smStateBasicTestAbsType_action_a_history(),
      m_smStateBasicTestAbsType_action_b_history() {}

BasicTestAbsType ::~BasicTestAbsType() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicTestAbsType ::FppTest_SmState_BasicTestAbsType_action_a(SmId smId,
                                                                  FppTest_SmState_BasicTestAbsType::Signal signal) {
    this->m_smStateBasicTestAbsType_action_a_history.push(signal);
}

void BasicTestAbsType ::FppTest_SmState_BasicTestAbsType_action_b(SmId smId,
                                                                  FppTest_SmState_BasicTestAbsType::Signal signal,
                                                                  const SmHarness::TestAbsType& value) {
    this->m_smStateBasicTestAbsType_action_b_history.push(signal, value);
}


}  // namespace SmInstanceState

}  // namespace FppTest
