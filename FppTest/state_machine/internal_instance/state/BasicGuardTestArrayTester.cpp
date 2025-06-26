// ======================================================================
// \title  BasicGuardTestArrayTester.cpp
// \author m-aleem
// \brief  cpp file for BasicGuardTestArrayTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestArrayTester.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicGuardTestArrayTester ::
  BasicGuardTestArrayTester(
      BasicGuardTestArray& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicGuardTestArrayTester ::
  testTrue()
{
    this->m_comp.m_smStateBasicGuardTestArray_action_a_history.clear();
    this->m_comp.m_smStateBasicGuardTestArray_guard_g.reset();
    this->m_comp.m_smStateBasicGuardTestArray_guard_g.setReturnValue(true);
    this->m_comp.init(BasicGuardTestArray::queueDepth, BasicGuardTestArray::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestArray_getState(), BasicGuardTestArray::SmState_BasicGuardTestArray::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_guard_g.getCallHistory().getSize(), 0);
    const auto value = SmHarness::Pick::testArray();
    this->m_comp.smStateBasicGuardTestArray_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestArray_getState(), BasicGuardTestArray::SmState_BasicGuardTestArray::State::T);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_guard_g.getCallHistory().getSignals().getItemAt(0),
              BasicGuardTestArray::SmState_BasicGuardTestArray::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_guard_g.getCallHistory().getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_action_a_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_action_a_history.getSignals().getItemAt(0),
              BasicGuardTestArray::SmState_BasicGuardTestArray::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_action_a_history.getValues().getItemAt(0), value);
}

void BasicGuardTestArrayTester ::
  testFalse()
{
    this->m_comp.m_smStateBasicGuardTestArray_action_a_history.clear();
    this->m_comp.m_smStateBasicGuardTestArray_guard_g.reset();
    this->m_comp.init(BasicGuardTestArray::queueDepth, BasicGuardTestArray::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestArray_getState(), BasicGuardTestArray::SmState_BasicGuardTestArray::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_guard_g.getCallHistory().getSize(), 0);
    const auto value = SmHarness::Pick::testArray();
    this->m_comp.smStateBasicGuardTestArray_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuardTestArray_getState(), BasicGuardTestArray::SmState_BasicGuardTestArray::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_guard_g.getCallHistory().getSignals().getItemAt(0),
              BasicGuardTestArray::SmState_BasicGuardTestArray::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_guard_g.getCallHistory().getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuardTestArray_action_a_history.getSize(), 0);
}

} // end namespace SmInstanceState

} // end namespace FppTest
