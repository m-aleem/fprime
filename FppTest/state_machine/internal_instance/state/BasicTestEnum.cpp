// ======================================================================
// \title  BasicTestEnum.cpp
// \author bocchino
// \brief  cpp file for BasicTestEnum component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicTestEnum.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicTestEnum::BasicTestEnum(const char* const compName)
    : BasicTestEnumComponentBase(compName),
      m_smStateBasicTestEnum_action_a_history(),
      m_smStateBasicTestEnum_action_b_history() {}

BasicTestEnum::~BasicTestEnum() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicTestEnum::FppTest_SmState_BasicTestEnum_action_a(SmId smId, FppTest_SmState_BasicTestEnum::Signal signal) {
    this->m_smStateBasicTestEnum_action_a_history.push(signal);
}

void BasicTestEnum::FppTest_SmState_BasicTestEnum_action_b(SmId smId,
                                                           FppTest_SmState_BasicTestEnum::Signal signal,
                                                           const SmHarness::TestEnum& value) {
    this->m_smStateBasicTestEnum_action_b_history.push(signal, value);
}


}  // namespace SmInstanceState

}  // namespace FppTest
