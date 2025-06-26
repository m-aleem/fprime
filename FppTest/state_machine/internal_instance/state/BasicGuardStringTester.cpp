// ======================================================================
// \title  BasicGuardStringTester.cpp
// \author m-aleem
// \brief  cpp file for BasicGuardStringTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/state/FppConstantsAc.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardStringTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicGuardStringTester ::
  BasicGuardStringTester(
      BasicGuardString& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicGuardStringTester ::
  testTrue()
{
    this->m_comp.m_smStateBasicGuardString_action_a_history.clear();
    this->m_comp.m_smStateBasicGuardString_guard_g.reset();
    this->m_comp.m_smStateBasicGuardString_guard_g.setReturnValue(true);
    this->m_comp.init(BasicGuardString::queueDepth, BasicGuardString::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuardString_getState(), BasicGuardString::SmState_BasicGuardString::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_guard_g.getCallHistory().getSize(), 0);
    Fw::String value;
    SmHarness::Pick::string(value, SmState::basicGuardStringSize);
    this->m_comp.smStateBasicGuardString_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuardString_getState(), BasicGuardString::SmState_BasicGuardString::State::T);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_guard_g.getCallHistory().getSignals().getItemAt(0),
              BasicGuardString::SmState_BasicGuardString::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_guard_g.getCallHistory().getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_action_a_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_action_a_history.getSignals().getItemAt(0),
              BasicGuardString::SmState_BasicGuardString::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_action_a_history.getValues().getItemAt(0), value);
}

void BasicGuardStringTester ::
  testFalse()
{
    this->m_comp.m_smStateBasicGuardString_action_a_history.clear();
    this->m_comp.m_smStateBasicGuardString_guard_g.reset();
    this->m_comp.m_smStateBasicGuardString_guard_g.setReturnValue(false);
    this->m_comp.init(BasicGuardString::queueDepth, BasicGuardString::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuardString_getState(), BasicGuardString::SmState_BasicGuardString::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_guard_g.getCallHistory().getSize(), 0);
    Fw::String value;
    SmHarness::Pick::string(value, SmState::basicGuardStringSize);
    this->m_comp.smStateBasicGuardString_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuardString_getState(), BasicGuardString::SmState_BasicGuardString::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_guard_g.getCallHistory().getSignals().getItemAt(0),
              BasicGuardString::SmState_BasicGuardString::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_guard_g.getCallHistory().getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardString_action_a_history.getSize(), 0);
}

} // end namespace SmInstanceState

} // end namespace FppTest
