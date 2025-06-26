// ======================================================================
// \title  StateToChildTester.cpp
// \author m-aleem
// \brief  cpp file for StateToChildTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/StateToChildTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

StateToChildTester ::
  StateToChildTester(
      StateToChild& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void StateToChildTester ::
  testInit()
{
    this->m_comp.m_smStateStateToChild_actionHistory.clear();
    this->m_comp.init(StateToChild::queueDepth, StateToChild::instanceId);
    ASSERT_EQ(this->m_comp.smStateStateToChild_getState(), StateToChild::SmState_StateToChild::State::S1_S2);
    ASSERT_EQ(this->m_comp.m_smStateStateToChild_actionHistory.getSize(), 1);
    const auto& signals = this->m_comp.m_smStateStateToChild_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToChild_actionHistory.getValues();
    ASSERT_EQ(signals.getItemAt(0), StateToChild::SmState_StateToChild::Signal::__FPRIME_AC_INITIAL_TRANSITION);
    ASSERT_EQ(actions.getItemAt(0), StateToChild::ActionId::ENTER_S2);
}

void StateToChildTester ::
  testS2_to_S2()
{
    this->m_comp.m_smStateStateToChild_actionHistory.clear();
    this->m_comp.init(StateToChild::queueDepth, StateToChild::instanceId);
    this->m_comp.m_smStateStateToChild_actionHistory.clear();
    this->m_comp.smStateStateToChild_sendSignal_S1_to_S2();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateStateToChild_getState(), StateToChild::SmState_StateToChild::State::S1_S2);
    const FwIndexType expectedSize = 3;
    ASSERT_EQ(this->m_comp.m_smStateStateToChild_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToChild_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToChild_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToChild::SmState_StateToChild::Signal::S1_to_S2);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToChild::ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), StateToChild::ActionId::A);
    ASSERT_EQ(actions.getItemAt(2), StateToChild::ActionId::ENTER_S2);
}

void StateToChildTester ::
  testS2_to_S3()
{
    this->m_comp.m_smStateStateToChild_actionHistory.clear();
    this->m_comp.init(StateToChild::queueDepth, StateToChild::instanceId);
    this->m_comp.m_smStateStateToChild_actionHistory.clear();
    this->m_comp.smStateStateToChild_sendSignal_S2_to_S3();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateStateToChild_getState(), StateToChild::SmState_StateToChild::State::S1_S3);
    const FwIndexType expectedSize = 2;
    ASSERT_EQ(this->m_comp.m_smStateStateToChild_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToChild_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToChild_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToChild::SmState_StateToChild::Signal::S2_to_S3);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToChild::ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), StateToChild::ActionId::ENTER_S3);
}

void StateToChildTester ::
  testS3_to_S2()
{
    this->m_comp.m_smStateStateToChild_actionHistory.clear();
    this->m_comp.init(StateToChild::queueDepth, StateToChild::instanceId);
    {
        this->m_comp.m_smStateStateToChild_actionHistory.clear();
        this->m_comp.smStateStateToChild_sendSignal_S2_to_S3();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
        ASSERT_EQ(this->m_comp.smStateStateToChild_getState(), StateToChild::SmState_StateToChild::State::S1_S3);
    }
    {
        this->m_comp.m_smStateStateToChild_actionHistory.clear();
        this->m_comp.smStateStateToChild_sendSignal_S1_to_S2();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
        ASSERT_EQ(this->m_comp.smStateStateToChild_getState(), StateToChild::SmState_StateToChild::State::S1_S2);
    }
    const FwIndexType expectedSize = 3;
    ASSERT_EQ(this->m_comp.m_smStateStateToChild_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToChild_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToChild_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToChild::SmState_StateToChild::Signal::S1_to_S2);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToChild::ActionId::EXIT_S3);
    ASSERT_EQ(actions.getItemAt(1), StateToChild::ActionId::A);
    ASSERT_EQ(actions.getItemAt(2), StateToChild::ActionId::ENTER_S2);
}

} // end namespace SmInstanceState

} // end namespace FppTest
