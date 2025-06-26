// ======================================================================
// \title  BasicTestStruct.cpp
// \author bocchino
// \brief  cpp file for BasicTestStruct component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicTestStruct.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicTestStruct::BasicTestStruct(const char* const compName)
    : BasicTestStructComponentBase(compName),
      m_smStateBasicTestStruct_action_a_history(),
      m_smStateBasicTestStruct_action_b_history() {}

BasicTestStruct::~BasicTestStruct() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicTestStruct::FppTest_SmState_BasicTestStruct_action_a(SmId smId,
                                                               FppTest_SmState_BasicTestStruct::Signal signal) {
    this->m_smStateBasicTestStruct_action_a_history.push(signal);
}

void BasicTestStruct::FppTest_SmState_BasicTestStruct_action_b(SmId smId,
                                                               FppTest_SmState_BasicTestStruct::Signal signal,
                                                               const SmHarness::TestStruct& value) {
    this->m_smStateBasicTestStruct_action_b_history.push(signal, value);
}


}  // namespace SmInstanceState

}  // namespace FppTest
