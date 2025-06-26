// ======================================================================
// \title  Internal.cpp
// \author bocchino
// \brief  cpp file for Internal component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/Internal.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Internal::Internal(const char* const compName)
    : InternalComponentBase(compName), m_smStateInternal_action_a_history() {}

Internal::~Internal() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void Internal::FppTest_SmState_Internal_action_a(SmId smId, FppTest_SmState_Internal::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateInternal);
    this->m_smStateInternal_action_a_history.push(signal);
}


}  // namespace SmInstanceState

}  // namespace FppTest
