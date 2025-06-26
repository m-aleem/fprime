// ======================================================================
// \title  BasicTestArrayTester.cpp
// \author m-aleem
// \brief  cpp file for BasicTestArrayTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicTestArrayTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicTestArrayTester ::
  BasicTestArrayTester(
      BasicTestArray& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicTestArrayTester ::
  test()
{
    this->m_comp.m_smStateBasicTestArray_action_a_history.clear();
    this->m_comp.m_smStateBasicTestArray_action_b_history.clear();
    this->m_comp.init(BasicTestArray::queueDepth, BasicTestArray::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicTestArray_getState(), BasicTestArray::SmState_BasicTestArray::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestArray_action_a_history.getSize(), 0);
    const SmHarness::TestArray value = SmHarness::Pick::testArray();
    this->m_comp.smStateBasicTestArray_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicTestArray_getState(), BasicTestArray::SmState_BasicTestArray::State::T);
    const FwIndexType expectedASize = 5;
    ASSERT_EQ(this->m_comp.m_smStateBasicTestArray_action_a_history.getSize(), expectedASize);
    for (FwIndexType i = 0; i < expectedASize; i++) {
        ASSERT_EQ(this->m_comp.m_smStateBasicTestArray_action_a_history.getItemAt(i), BasicTestArray::SmState_BasicTestArray::Signal::s);
    }
    ASSERT_EQ(this->m_comp.m_smStateBasicTestArray_action_b_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestArray_action_b_history.getSignals().getItemAt(0),
              BasicTestArray::SmState_BasicTestArray::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestArray_action_b_history.getValues().getItemAt(0), value);
}

} // end namespace SmInstanceState

} // end namespace FppTest
