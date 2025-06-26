// ======================================================================
// \title  BasicString.cpp
// \author bocchino
// \brief  cpp file for BasicString component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/state/FppConstantsAc.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicString.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicString ::BasicString(const char* const compName)
    : BasicStringComponentBase(compName),
      m_smStateBasicString_action_a_history(),
      m_smStateBasicString_action_b_history() {}

BasicString ::~BasicString() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicString ::FppTest_SmState_BasicString_action_a(SmId smId, FppTest_SmState_BasicString::Signal signal) {
    this->m_smStateBasicString_action_a_history.push(signal);
}

void BasicString ::FppTest_SmState_BasicString_action_b(SmId smId,
                                                        FppTest_SmState_BasicString::Signal signal,
                                                        const Fw::StringBase& value) {
    this->m_smStateBasicString_action_b_history.push(signal, Fw::String(value));
}


}  // namespace SmInstanceState

}  // namespace FppTest
