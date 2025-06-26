// ======================================================================
// \title  BasicTestEnumTester.cpp
// \author m-aleem
// \brief  cpp file for BasicTestEnumTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicTestEnumTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicTestEnumTester ::
  BasicTestEnumTester(
      BasicTestEnum& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicTestEnumTester ::
  test()
{
    this->m_comp.m_smStateBasicTestEnum_action_a_history.clear();
    this->m_comp.m_smStateBasicTestEnum_action_b_history.clear();
    this->m_comp.init(BasicTestEnum::queueDepth, BasicTestEnum::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicTestEnum_getState(), BasicTestEnum::SmState_BasicTestEnum::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestEnum_action_a_history.getSize(), 0);
    const SmHarness::TestEnum value = SmHarness::Pick::testEnum();
    this->m_comp.smStateBasicTestEnum_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicTestEnum_getState(), BasicTestEnum::SmState_BasicTestEnum::State::T);
    const FwIndexType expectedASize = 5;
    ASSERT_EQ(this->m_comp.m_smStateBasicTestEnum_action_a_history.getSize(), expectedASize);
    for (FwIndexType i = 0; i < expectedASize; i++) {
        ASSERT_EQ(this->m_comp.m_smStateBasicTestEnum_action_a_history.getItemAt(i), BasicTestEnum::SmState_BasicTestEnum::Signal::s);
    }
    ASSERT_EQ(this->m_comp.m_smStateBasicTestEnum_action_b_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestEnum_action_b_history.getSignals().getItemAt(0),
              BasicTestEnum::SmState_BasicTestEnum::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestEnum_action_b_history.getValues().getItemAt(0), value);
}

} // end namespace SmInstanceState

} // end namespace FppTest
