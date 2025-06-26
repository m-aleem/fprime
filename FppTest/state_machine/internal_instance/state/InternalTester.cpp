// ======================================================================
// \title  InternalTester.cpp
// \author m-aleem
// \brief  cpp file for InternalTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/InternalTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

InternalTester ::
  InternalTester(
      Internal& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void InternalTester ::
  testInit()
{
    this->m_comp.m_smStateInternal_action_a_history.clear();
    this->m_comp.init(Internal::queueDepth, Internal::instanceId);
    ASSERT_EQ(this->m_comp.smStateInternal_getState(), Internal::SmState_Internal::State::S1_S2);
    ASSERT_EQ(this->m_comp.m_smStateInternal_action_a_history.getSize(), 0);
}

void InternalTester ::
  testS2_internal()
{
    this->m_comp.m_smStateInternal_action_a_history.clear();
    this->m_comp.init(Internal::queueDepth, Internal::instanceId);
    ASSERT_EQ(this->m_comp.smStateInternal_getState(), Internal::SmState_Internal::State::S1_S2);
    this->m_comp.smStateInternal_sendSignal_S1_internal();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateInternal_getState(), Internal::SmState_Internal::State::S1_S2);
    ASSERT_EQ(this->m_comp.m_smStateInternal_action_a_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateInternal_action_a_history.getItemAt(0), Internal::SmState_Internal::Signal::S1_internal);
}

void InternalTester ::
  testS2_to_S3()
{
    this->m_comp.m_smStateInternal_action_a_history.clear();
    this->m_comp.init(Internal::queueDepth, Internal::instanceId);
    ASSERT_EQ(this->m_comp.smStateInternal_getState(), Internal::SmState_Internal::State::S1_S2);
    this->m_comp.smStateInternal_sendSignal_S2_to_S3();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateInternal_getState(), Internal::SmState_Internal::State::S1_S3);
    ASSERT_EQ(this->m_comp.m_smStateInternal_action_a_history.getSize(), 0);
}

void InternalTester ::
  testS3_internal()
{
    this->m_comp.m_smStateInternal_action_a_history.clear();
    this->m_comp.init(Internal::queueDepth, Internal::instanceId);
    ASSERT_EQ(this->m_comp.smStateInternal_getState(), Internal::SmState_Internal::State::S1_S2);
    {
        this->m_comp.smStateInternal_sendSignal_S2_to_S3();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
        ASSERT_EQ(this->m_comp.smStateInternal_getState(), Internal::SmState_Internal::State::S1_S3);
    }
    {
        this->m_comp.smStateInternal_sendSignal_S1_internal();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
        ASSERT_EQ(this->m_comp.smStateInternal_getState(), Internal::SmState_Internal::State::S1_S3);
        ASSERT_EQ(this->m_comp.m_smStateInternal_action_a_history.getSize(), 1);
        ASSERT_EQ(this->m_comp.m_smStateInternal_action_a_history.getItemAt(0), Internal::SmState_Internal::Signal::S1_internal);
    }
}

} // end namespace SmInstanceState

} // end namespace FppTest
