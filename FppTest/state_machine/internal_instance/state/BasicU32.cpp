// ======================================================================
// \title  BasicU32.cpp
// \author bocchino
// \brief  cpp file for BasicU32 component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicU32.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicU32::BasicU32(const char* const compName)
    : BasicU32ComponentBase(compName), m_smStateBasicU32_action_a_history(), m_smStateBasicU32_action_b_history() {}

BasicU32::~BasicU32() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicU32::FppTest_SmState_BasicU32_action_a(SmId smId, FppTest_SmState_BasicU32::Signal signal) {
    this->m_smStateBasicU32_action_a_history.push(signal);
}

void BasicU32::FppTest_SmState_BasicU32_action_b(SmId smId, FppTest_SmState_BasicU32::Signal signal, U32 value) {
    this->m_smStateBasicU32_action_b_history.push(signal, value);
}


}  // namespace SmInstanceState

}  // namespace FppTest
