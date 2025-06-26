// ======================================================================
// \title  BasicTestAbsTypeTester.cpp
// \author m-aleem
// \brief  cpp file for BasicTestAbsTypeTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicTestAbsTypeTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicTestAbsTypeTester ::
  BasicTestAbsTypeTester(
      BasicTestAbsType& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicTestAbsTypeTester ::
  test()
{
    this->m_comp.m_smStateBasicTestAbsType_action_a_history.clear();
    this->m_comp.m_smStateBasicTestAbsType_action_b_history.clear();
    this->m_comp.init(BasicTestAbsType::queueDepth, BasicTestAbsType::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicTestAbsType_getState(), BasicTestAbsType::SmState_BasicTestAbsType::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestAbsType_action_a_history.getSize(), 0);
    const SmHarness::TestAbsType value = SmHarness::Pick::testAbsType();
    this->m_comp.smStateBasicTestAbsType_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicTestAbsType_getState(), BasicTestAbsType::SmState_BasicTestAbsType::State::T);
    const FwIndexType expectedASize = 5;
    ASSERT_EQ(this->m_comp.m_smStateBasicTestAbsType_action_a_history.getSize(), expectedASize);
    for (FwIndexType i = 0; i < expectedASize; i++) {
        ASSERT_EQ(this->m_comp.m_smStateBasicTestAbsType_action_a_history.getItemAt(i), BasicTestAbsType::SmState_BasicTestAbsType::Signal::s);
    }
    ASSERT_EQ(this->m_comp.m_smStateBasicTestAbsType_action_b_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestAbsType_action_b_history.getSignals().getItemAt(0),
              BasicTestAbsType::SmState_BasicTestAbsType::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicTestAbsType_action_b_history.getValues().getItemAt(0), value);
}

} // end namespace SmInstanceState

} // end namespace FppTest
