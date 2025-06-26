// ======================================================================
// \title  BasicTester.cpp
// \author m-aleem
// \brief  cpp file for BasicTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicTester ::
  BasicTester(
      Basic& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicTester ::
  test()
{
    this->m_comp.m_basic1_action_a_history.clear();
    this->m_comp.m_smStateBasic1_action_a_history.clear();
    this->m_comp.init(Basic::queueDepth, Basic::instanceId);
    ASSERT_EQ(this->m_comp.basic1_getState(), Basic::Basic_Basic::State::S);
    ASSERT_EQ(this->m_comp.smStateBasic1_getState(), Basic::SmState_Basic::State::S);
    ASSERT_EQ(this->m_comp.m_basic1_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_basic2_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasic1_action_a_history.getSize(), 0);
    {
        // Send signal s to basic1
        this->m_comp.basic1_sendSignal_s();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
        ASSERT_EQ(this->m_comp.basic1_getState(), Basic::Basic_Basic::State::T);
        const FwIndexType expectedSize = 6;
        ASSERT_EQ(this->m_comp.m_basic1_action_a_history.getSize(), expectedSize);
        for (FwIndexType i = 0; i < expectedSize; i++) {
            ASSERT_EQ(this->m_comp.m_basic1_action_a_history.getItemAt(i), Basic::Basic_Basic::Signal::s);
        }
    }
    {
        // Send signal s to basic2
        this->m_comp.basic2_sendSignal_s();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
        ASSERT_EQ(this->m_comp.basic2_getState(), Basic::Basic_Basic::State::T);
        const FwIndexType expectedSize = 6;
        ASSERT_EQ(this->m_comp.m_basic2_action_a_history.getSize(), expectedSize);
        for (FwIndexType i = 0; i < expectedSize; i++) {
            ASSERT_EQ(this->m_comp.m_basic2_action_a_history.getItemAt(i), Basic::Basic_Basic::Signal::s);
        }
    }
    {
        // Send signal s to smStateBasic1
        this->m_comp.smStateBasic1_sendSignal_s();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
        ASSERT_EQ(this->m_comp.smStateBasic1_getState(), Basic::SmState_Basic::State::T);
        const FwIndexType expectedSize = 6;
        ASSERT_EQ(this->m_comp.m_smStateBasic1_action_a_history.getSize(), expectedSize);
        for (FwIndexType i = 0; i < expectedSize; i++) {
            ASSERT_EQ(this->m_comp.m_smStateBasic1_action_a_history.getItemAt(i), Basic::SmState_Basic::Signal::s);
        }
    }
    {
        // Send signal s to smStateBasic2
        this->m_comp.smStateBasic2_sendSignal_s();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
        ASSERT_EQ(this->m_comp.smStateBasic2_getState(), Basic::SmState_Basic::State::T);
        const FwIndexType expectedSize = 6;
        ASSERT_EQ(this->m_comp.m_smStateBasic2_action_a_history.getSize(), expectedSize);
        for (FwIndexType i = 0; i < expectedSize; i++) {
            ASSERT_EQ(this->m_comp.m_smStateBasic2_action_a_history.getItemAt(i), Basic::SmState_Basic::Signal::s);
        }
    }
}

} // end namespace SmInstanceState

} // end namespace FppTest
