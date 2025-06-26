// ======================================================================
// \title  StateToStateTester.cpp
// \author m-aleem
// \brief  cpp file for StateToStateTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/StateToStateTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

StateToStateTester ::
  StateToStateTester(
      StateToState& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void StateToStateTester ::
  testInit()
{
    this->m_comp.m_smStateStateToState_actionHistory.clear();
    this->m_comp.init(StateToState::queueDepth, StateToState::instanceId);
    ASSERT_EQ(this->m_comp.smStateStateToState_getState(), StateToState::SmState_StateToState::State::S1_S2);
    const FwIndexType expectedSize = 2;
    ASSERT_EQ(this->m_comp.m_smStateStateToState_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToState_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToState_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToState::SmState_StateToState::Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToState::ActionId::ENTER_S1);
    ASSERT_EQ(actions.getItemAt(1), StateToState::ActionId::ENTER_S2);
}

void StateToStateTester ::
  testS2_to_S3()
{
    this->m_comp.m_smStateStateToState_actionHistory.clear();
    this->m_comp.init(StateToState::queueDepth, StateToState::instanceId);
    this->m_comp.m_smStateStateToState_actionHistory.clear();
    this->m_comp.smStateStateToState_sendSignal_S2_to_S3();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateStateToState_getState(), StateToState::SmState_StateToState::State::S1_S3);
    const FwIndexType expectedSize = 2;
    ASSERT_EQ(this->m_comp.m_smStateStateToState_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToState_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToState_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToState::SmState_StateToState::Signal::S2_to_S3);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToState::ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), StateToState::ActionId::ENTER_S3);
}

void StateToStateTester ::
  testS2_to_S4()
{
    this->m_comp.m_smStateStateToState_actionHistory.clear();
    this->m_comp.init(StateToState::queueDepth, StateToState::instanceId);
    this->m_comp.m_smStateStateToState_actionHistory.clear();
    this->m_comp.smStateStateToState_sendSignal_S1_to_S4();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateStateToState_getState(), StateToState::SmState_StateToState::State::S4_S5);
    const FwIndexType expectedSize = 5;
    ASSERT_EQ(this->m_comp.m_smStateStateToState_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToState_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToState_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToState::SmState_StateToState::Signal::S1_to_S4);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToState::ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), StateToState::ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), StateToState::ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), StateToState::ActionId::ENTER_S4);
    ASSERT_EQ(actions.getItemAt(4), StateToState::ActionId::ENTER_S5);
}

void StateToStateTester ::
  testS2_to_S5()
{
    this->m_comp.m_smStateStateToState_actionHistory.clear();
    this->m_comp.init(StateToState::queueDepth, StateToState::instanceId);
    this->m_comp.m_smStateStateToState_actionHistory.clear();
    this->m_comp.smStateStateToState_sendSignal_S1_to_S5();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateStateToState_getState(), StateToState::SmState_StateToState::State::S4_S5);
    const FwIndexType expectedSize = 5;
    ASSERT_EQ(this->m_comp.m_smStateStateToState_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToState_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToState_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToState::SmState_StateToState::Signal::S1_to_S5);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToState::ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), StateToState::ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), StateToState::ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), StateToState::ActionId::ENTER_S4);
    ASSERT_EQ(actions.getItemAt(4), StateToState::ActionId::ENTER_S5);
}

void StateToStateTester ::
  testS3_to_S4()
{
    this->m_comp.m_smStateStateToState_actionHistory.clear();
    this->m_comp.init(StateToState::queueDepth, StateToState::instanceId);
    {
        this->m_comp.m_smStateStateToState_actionHistory.clear();
        this->m_comp.smStateStateToState_sendSignal_S2_to_S3();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    }
    {
        this->m_comp.m_smStateStateToState_actionHistory.clear();
        this->m_comp.smStateStateToState_sendSignal_S1_to_S4();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    }
    ASSERT_EQ(this->m_comp.smStateStateToState_getState(), StateToState::SmState_StateToState::State::S4_S5);
    const FwIndexType expectedSize = 5;
    ASSERT_EQ(this->m_comp.m_smStateStateToState_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToState_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToState_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToState::SmState_StateToState::Signal::S1_to_S4);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToState::ActionId::EXIT_S3);
    ASSERT_EQ(actions.getItemAt(1), StateToState::ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), StateToState::ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), StateToState::ActionId::ENTER_S4);
    ASSERT_EQ(actions.getItemAt(4), StateToState::ActionId::ENTER_S5);
}

void StateToStateTester ::
  testS3_to_S5()
{
    this->m_comp.m_smStateStateToState_actionHistory.clear();
    this->m_comp.init(StateToState::queueDepth, StateToState::instanceId);
    {
        this->m_comp.m_smStateStateToState_actionHistory.clear();
        this->m_comp.smStateStateToState_sendSignal_S2_to_S3();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    }
    {
        this->m_comp.m_smStateStateToState_actionHistory.clear();
        this->m_comp.smStateStateToState_sendSignal_S1_to_S5();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    }
    ASSERT_EQ(this->m_comp.smStateStateToState_getState(), StateToState::SmState_StateToState::State::S4_S5);
    const FwIndexType expectedSize = 5;
    ASSERT_EQ(this->m_comp.m_smStateStateToState_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToState_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToState_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToState::SmState_StateToState::Signal::S1_to_S5);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToState::ActionId::EXIT_S3);
    ASSERT_EQ(actions.getItemAt(1), StateToState::ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), StateToState::ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), StateToState::ActionId::ENTER_S4);
    ASSERT_EQ(actions.getItemAt(4), StateToState::ActionId::ENTER_S5);
}

} // end namespace SmInstanceState

} // end namespace FppTest
