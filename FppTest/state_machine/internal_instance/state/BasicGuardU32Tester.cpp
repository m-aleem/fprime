// ======================================================================
// \title  BasicGuardU32Tester.cpp
// \author m-aleem
// \brief  cpp file for BasicGuardU32Tester class
// ======================================================================

#include <gtest/gtest.h>
#include "STest/STest/Random/Random.hpp"

#include "FppTest/state_machine/internal_instance/state/BasicGuardU32Tester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicGuardU32Tester ::
  BasicGuardU32Tester(
      BasicGuardU32& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicGuardU32Tester ::
  testTrue()
{
    this->m_comp.m_smStateBasicGuardU32_action_a_history.clear();
    this->m_comp.m_smStateBasicGuardU32_guard_g.reset();
    this->m_comp.m_smStateBasicGuardU32_guard_g.setReturnValue(true);
    this->m_comp.init(BasicGuardU32::queueDepth, BasicGuardU32::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuardU32_getState(), BasicGuardU32::SmState_BasicGuardU32::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_guard_g.getCallHistory().getSize(), 0);
    const U32 value = STest::Pick::any();
    this->m_comp.smStateBasicGuardU32_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuardU32_getState(), BasicGuardU32::SmState_BasicGuardU32::State::T);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_guard_g.getCallHistory().getSignals().getItemAt(0),
              BasicGuardU32::SmState_BasicGuardU32::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_guard_g.getCallHistory().getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_action_a_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_action_a_history.getSignals().getItemAt(0),
              BasicGuardU32::SmState_BasicGuardU32::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_action_a_history.getValues().getItemAt(0), value);
}

void BasicGuardU32Tester ::
  testFalse()
{
    this->m_comp.m_smStateBasicGuardU32_action_a_history.clear();
    this->m_comp.m_smStateBasicGuardU32_guard_g.reset();
    this->m_comp.init(BasicGuardU32::queueDepth, BasicGuardU32::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuardU32_getState(), BasicGuardU32::SmState_BasicGuardU32::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_guard_g.getCallHistory().getSize(), 0);
    const U32 value = STest::Pick::any();
    this->m_comp.smStateBasicGuardU32_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuardU32_getState(), BasicGuardU32::SmState_BasicGuardU32::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_guard_g.getCallHistory().getSignals().getItemAt(0),
              BasicGuardU32::SmState_BasicGuardU32::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_guard_g.getCallHistory().getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardU32_action_a_history.getSize(), 0);
}

} // end namespace SmInstanceState

} // end namespace FppTest
