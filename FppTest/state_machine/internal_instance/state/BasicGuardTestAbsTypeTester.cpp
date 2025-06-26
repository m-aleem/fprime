// ======================================================================
// \title  BasicGuardTestAbsTypeTester.cpp
// \author m-aleem
// \brief  cpp file for BasicGuardTestAbsTypeTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestAbsTypeTester.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicGuardTestAbsTypeTester ::
  BasicGuardTestAbsTypeTester(
      BasicGuardTestAbsType& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicGuardTestAbsTypeTester ::
  testFalse()
{
    this->m_comp.m_smStateBasicGuardTestAbsType_action_a_history.clear();
    this->m_comp.m_smStateBasicGuardTestAbsType_guard_g.reset();
    this->m_comp.init(BasicGuardTestAbsType::queueDepth, BasicGuardTestAbsType::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestAbsType_getState(), BasicGuardTestAbsType::SmState_BasicGuardTestAbsType::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getSize(), 0);
    this->m_comp.m_value = SmHarness::Pick::testAbsType();
    this->m_comp.smStateBasicGuardTestAbsType_sendSignal_s(this->m_comp.m_value);
    ASSERT_FALSE(this->m_comp.m_hookCalled);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestAbsType_getState(), BasicGuardTestAbsType::SmState_BasicGuardTestAbsType::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getSignals().getItemAt(0),
              BasicGuardTestAbsType::SmState_BasicGuardTestAbsType::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getValues().getItemAt(0), this->m_comp.m_value);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_action_a_history.getSize(), 0);
}

void BasicGuardTestAbsTypeTester ::
  testTrue()
{
    this->m_comp.m_smStateBasicGuardTestAbsType_action_a_history.clear();
    this->m_comp.m_smStateBasicGuardTestAbsType_guard_g.reset();
    this->m_comp.m_smStateBasicGuardTestAbsType_guard_g.setReturnValue(true);
    this->m_comp.init(BasicGuardTestAbsType::queueDepth, BasicGuardTestAbsType::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestAbsType_getState(), BasicGuardTestAbsType::SmState_BasicGuardTestAbsType::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getSize(), 0);
    this->m_comp.m_value = SmHarness::Pick::testAbsType();
    this->m_comp.smStateBasicGuardTestAbsType_sendSignal_s(this->m_comp.m_value);
    ASSERT_FALSE(this->m_comp.m_hookCalled);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestAbsType_getState(), BasicGuardTestAbsType::SmState_BasicGuardTestAbsType::State::T);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getSignals().getItemAt(0),
              BasicGuardTestAbsType::SmState_BasicGuardTestAbsType::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getValues().getItemAt(0), this->m_comp.m_value);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_action_a_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_action_a_history.getSignals().getItemAt(0),
              BasicGuardTestAbsType::SmState_BasicGuardTestAbsType::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestAbsType_action_a_history.getValues().getItemAt(0), this->m_comp.m_value);
}

void BasicGuardTestAbsTypeTester ::
  testOverflow()
{
    this->m_comp.init(BasicGuardTestAbsType::queueDepth, BasicGuardTestAbsType::instanceId);
    this->m_comp.m_value = SmHarness::Pick::testAbsType();
    for (FwSizeType i = 0; i < BasicGuardTestAbsType::queueDepth; i++) {
        this->m_comp.smStateBasicGuardTestAbsType_sendSignal_s(this->m_comp.m_value);
        ASSERT_FALSE(this->m_comp.m_hookCalled);
    }
    this->m_comp.smStateBasicGuardTestAbsType_sendSignal_s(this->m_comp.m_value);
    ASSERT_TRUE(this->m_comp.m_hookCalled);
}

} // end namespace SmInstanceState

} // end namespace FppTest
