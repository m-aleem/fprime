// ======================================================================
// \title  BasicU32Tester.cpp
// \author m-aleem
// \brief  cpp file for BasicU32Tester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicU32Tester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicU32Tester ::
  BasicU32Tester(
      BasicU32& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicU32Tester ::
  test()
{
    this->m_comp.m_smStateBasicU32_action_a_history.clear();
    this->m_comp.m_smStateBasicU32_action_b_history.clear();
    this->m_comp.init(BasicU32::queueDepth, BasicU32::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicU32_getState(), BasicU32::SmState_BasicU32::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicU32_action_a_history.getSize(), 0);
    const U32 value = STest::Pick::any();
    this->m_comp.smStateBasicU32_sendSignal_s(value);
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicU32_getState(), BasicU32::SmState_BasicU32::State::T);
    const FwIndexType expectedASize = 5;
    ASSERT_EQ(this->m_comp.m_smStateBasicU32_action_a_history.getSize(), expectedASize);
    for (FwIndexType i = 0; i < expectedASize; i++) {
        ASSERT_EQ(this->m_comp.m_smStateBasicU32_action_a_history.getItemAt(i), BasicU32::SmState_BasicU32::Signal::s);
    }
    ASSERT_EQ(this->m_comp.m_smStateBasicU32_action_b_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicU32_action_b_history.getSignals().getItemAt(0), BasicU32::SmState_BasicU32::Signal::s);
    ASSERT_EQ(this->m_comp.m_smStateBasicU32_action_b_history.getValues().getItemAt(0), value);
}

} // end namespace SmInstanceState

} // end namespace FppTest
