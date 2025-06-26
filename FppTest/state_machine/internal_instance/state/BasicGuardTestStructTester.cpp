// ======================================================================
// \title  BasicGuardTestStructTester.cpp
// \author m-aleem
// \brief  cpp file for BasicGuardTestStructTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestStructTester.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicGuardTestStructTester ::
  BasicGuardTestStructTester(
      BasicGuardTestStruct& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicGuardTestStructTester ::
  testTrue()
{
    this->m_comp.m_smStateBasicGuardTestStruct_action_a_history.clear();
    this->m_comp.m_smStateBasicGuardTestStruct_guard_g.reset();
    this->m_comp.m_smStateBasicGuardTestStruct_guard_g.setReturnValue(true);
    this->m_comp.init(BasicGuardTestStruct::queueDepth, BasicGuardTestStruct::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestStruct_getState(), BasicGuardTestStruct::SmState_BasicGuardTestStruct::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_guard_g.getCallHistory().getSize(), 0);
    const auto value = SmHarness::Pick::testStruct();
    this->m_comp.smStateBasicGuardTestStruct_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestStruct_getState(), BasicGuardTestStruct::SmState_BasicGuardTestStruct::State::T);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_guard_g.getCallHistory().getSignals().getItemAt(0),
              BasicGuardTestStruct::SmState_BasicGuardTestStruct::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_guard_g.getCallHistory().getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_action_a_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_action_a_history.getSignals().getItemAt(0),
              BasicGuardTestStruct::SmState_BasicGuardTestStruct::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_action_a_history.getValues().getItemAt(0), value);
}

void BasicGuardTestStructTester ::
  testFalse()
{
    this->m_comp.m_smStateBasicGuardTestStruct_action_a_history.clear();
    this->m_comp.m_smStateBasicGuardTestStruct_guard_g.reset();
    this->m_comp.init(BasicGuardTestStruct::queueDepth, BasicGuardTestStruct::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestStruct_getState(), BasicGuardTestStruct::SmState_BasicGuardTestStruct::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_guard_g.getCallHistory().getSize(), 0);
    const auto value = SmHarness::Pick::testStruct();
    this->m_comp.smStateBasicGuardTestStruct_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestStruct_getState(), BasicGuardTestStruct::SmState_BasicGuardTestStruct::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_guard_g.getCallHistory().getSignals().getItemAt(0),
              BasicGuardTestStruct::SmState_BasicGuardTestStruct::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_guard_g.getCallHistory().getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestStruct_action_a_history.getSize(), 0);
}

} // end namespace SmInstanceState

} // end namespace FppTest
