// ======================================================================
// \title  BasicInternal.cpp
// \author bocchino
// \brief  cpp file for BasicInternal component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicInternal.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicInternal::BasicInternal(const char* const compName)
    : BasicInternalComponentBase(compName), m_smStateBasicInternal_action_a_history() {}

BasicInternal::~BasicInternal() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicInternal::FppTest_SmState_BasicInternal_action_a(SmId smId, FppTest_SmState_BasicInternal::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateBasicInternal);
    this->m_smStateBasicInternal_action_a_history.push(signal);
}


}  // namespace SmInstanceState

}  // namespace FppTest
