// ======================================================================
// \title  BasicTestStructTester.cpp
// \author m-aleem
// \brief  cpp file for BasicTestStructTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicTestStructTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicTestStructTester ::
  BasicTestStructTester(
      BasicTestStruct& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicTestStructTester ::
  test()
{
    this->m_comp.m_smStateBasicTestStruct_action_a_history.clear();
    this->m_comp.m_smStateBasicTestStruct_action_b_history.clear();
    this->m_comp.init(BasicTestStruct::queueDepth, BasicTestStruct::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicTestStruct_getState(), BasicTestStruct::SmState_BasicTestStruct::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestStruct_action_a_history.getSize(), 0);
    const SmHarness::TestStruct value = SmHarness::Pick::testStruct();
    this->m_comp.smStateBasicTestStruct_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicTestStruct_getState(), BasicTestStruct::SmState_BasicTestStruct::State::T);
    const FwIndexType expectedASize = 5;
    ASSERT_EQ(this->m_comp.m_smStateBasicTestStruct_action_a_history.getSize(), expectedASize);
    for (FwIndexType i = 0; i < expectedASize; i++) {
        ASSERT_EQ(this->m_comp.m_smStateBasicTestStruct_action_a_history.getItemAt(i), BasicTestStruct::SmState_BasicTestStruct::Signal::s);
    }
    ASSERT_EQ(this->m_comp.m_smStateBasicTestStruct_action_b_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestStruct_action_b_history.getSignals().getItemAt(0),
              BasicTestStruct::SmState_BasicTestStruct::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestStruct_action_b_history.getValues().getItemAt(0), value);
}

} // end namespace SmInstanceState

} // end namespace FppTest
