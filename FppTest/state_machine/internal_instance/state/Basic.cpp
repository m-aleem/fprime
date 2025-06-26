// ======================================================================
// \title  Basic.cpp
// \author bocchino
// \brief  cpp file for Basic component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/Basic.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Basic ::Basic(const char* const compName)
    : BasicComponentBase(compName), m_basic1_action_a_history(), m_smStateBasic1_action_a_history() {}

Basic ::~Basic() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void Basic::schedIn_handler(FwIndexType portNum, U32 context) {
    // Nothing to do
}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void Basic ::FppTest_SmInstanceState_Basic_Basic_action_a(SmId smId,
                                                          FppTest_SmInstanceState_Basic_Basic::Signal signal) {
    ASSERT_TRUE((smId == SmId::basic1) || (smId == SmId::basic2));
    if (smId == SmId::basic1) {
        this->m_basic1_action_a_history.push(signal);
    } else {
        this->m_basic2_action_a_history.push(signal);
    }
}

void Basic ::FppTest_SmState_Basic_action_a(SmId smId, FppTest_SmState_Basic::Signal signal) {
    ASSERT_TRUE((smId == SmId::smStateBasic1) || (smId == SmId::smStateBasic2));
    if (smId == SmId::smStateBasic1) {
        this->m_smStateBasic1_action_a_history.push(signal);
    } else {
        this->m_smStateBasic2_action_a_history.push(signal);
    }
}


}  // namespace SmInstanceState

}  // namespace FppTest
