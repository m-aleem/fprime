// ======================================================================
// \title  BasicInternalTester.cpp
// \author m-aleem
// \brief  cpp file for BasicInternalTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicInternalTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicInternalTester ::
  BasicInternalTester(
      BasicInternal& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicInternalTester ::
  test()
{
    this->m_comp.m_smStateBasicInternal_action_a_history.clear();
    this->m_comp.init(BasicInternal::queueDepth, BasicInternal::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicInternal_getState(), BasicInternal::SmState_BasicInternal::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicInternal_action_a_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicInternal_action_a_history.getItemAt(0),
              BasicInternal::SmState_BasicInternal::Signal::__FPRIME_AC_INITIAL_TRANSITION);
    this->m_comp.m_smStateBasicInternal_action_a_history.clear();
    this->m_comp.smStateBasicInternal_sendSignal_s();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicInternal_getState(), BasicInternal::SmState_BasicInternal::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicInternal_action_a_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicInternal_action_a_history.getItemAt(0), BasicInternal::SmState_BasicInternal::Signal::s);
}

} // end namespace SmInstanceState

} // end namespace FppTest
