// ======================================================================
// \title  BasicStringTester.cpp
// \author m-aleem
// \brief  cpp file for BasicStringTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/state/FppConstantsAc.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicStringTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicStringTester ::
  BasicStringTester(
      BasicString& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicStringTester ::
  test()
{
    this->m_comp.m_smStateBasicString_action_a_history.clear();
    this->m_comp.m_smStateBasicString_action_b_history.clear();
    this->m_comp.init(BasicString::queueDepth, BasicString::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicString_getState(), BasicString::SmState_BasicString::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicString_action_a_history.getSize(), 0);
    Fw::String value;
    SmHarness::Pick::string(value, SmState::basicStringSize);
    this->m_comp.smStateBasicString_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicString_getState(), BasicString::SmState_BasicString::State::T);
    const FwIndexType expectedASize = 5;
    ASSERT_EQ(this->m_comp.m_smStateBasicString_action_a_history.getSize(), expectedASize);
    for (FwIndexType i = 0; i < expectedASize; i++) {
        ASSERT_EQ(this->m_comp.m_smStateBasicString_action_a_history.getItemAt(i), BasicString::SmState_BasicString::Signal::s);
    }
    ASSERT_EQ(this->m_comp.m_smStateBasicString_action_b_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicString_action_b_history.getSignals().getItemAt(0), BasicString::SmState_BasicString::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicString_action_b_history.getValues().getItemAt(0), value);
}

} // end namespace SmInstanceState

} // end namespace FppTest
