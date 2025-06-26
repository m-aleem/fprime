// ======================================================================
// \title  BasicTestArray.cpp
// \author bocchino
// \brief  cpp file for BasicTestArray component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicTestArray.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicTestArray::BasicTestArray(const char* const compName)
    : BasicTestArrayComponentBase(compName),
      m_smStateBasicTestArray_action_a_history(),
      m_smStateBasicTestArray_action_b_history() {}

BasicTestArray::~BasicTestArray() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicTestArray::FppTest_SmState_BasicTestArray_action_a(SmId smId, FppTest_SmState_BasicTestArray::Signal signal) {
    this->m_smStateBasicTestArray_action_a_history.push(signal);
}

void BasicTestArray::FppTest_SmState_BasicTestArray_action_b(SmId smId,
                                                             FppTest_SmState_BasicTestArray::Signal signal,
                                                             const SmHarness::TestArray& value) {
    this->m_smStateBasicTestArray_action_b_history.push(signal, value);
}


}  // namespace SmInstanceState

}  // namespace FppTest
