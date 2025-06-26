// ======================================================================
// \title  StateToChoiceTester.cpp
// \author m-aleem
// \brief  cpp file for StateToChoiceTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/StateToChoiceTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

StateToChoiceTester ::
  StateToChoiceTester(
      StateToChoice& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void StateToChoiceTester ::
  testInit()
{
    this->m_comp.m_smStateStateToChoice_actionHistory.clear();
    this->m_comp.init(StateToChoice::queueDepth, StateToChoice::instanceId);
    ASSERT_EQ(this->m_comp.smStateStateToChoice_getState(), StateToChoice::SmState_StateToChoice::State::S1_S2);
    const FwIndexType expectedSize = 2;
    ASSERT_EQ(this->m_comp.m_smStateStateToChoice_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToChoice_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToChoice_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToChoice::SmState_StateToChoice::Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToChoice::ActionId::ENTER_S1);
    ASSERT_EQ(actions.getItemAt(1), StateToChoice::ActionId::ENTER_S2);
}

void StateToChoiceTester ::
  testS2_to_C()
{
    this->m_comp.m_smStateStateToChoice_actionHistory.clear();
    this->m_comp.m_smStateStateToChoice_guard_g.reset();
    this->m_comp.m_smStateStateToChoice_guard_g.setReturnValue(true);
    this->m_comp.init(StateToChoice::queueDepth, StateToChoice::instanceId);
    this->m_comp.m_smStateStateToChoice_actionHistory.clear();
    this->m_comp.smStateStateToChoice_sendSignal_S1_to_C();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateStateToChoice_getState(), StateToChoice::SmState_StateToChoice::State::S4_S5);
    const FwIndexType expectedSize = 4;
    ASSERT_EQ(this->m_comp.m_smStateStateToChoice_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToChoice_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToChoice_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToChoice::SmState_StateToChoice::Signal::S1_to_C);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToChoice::ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), StateToChoice::ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), StateToChoice::ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), StateToChoice::ActionId::ENTER_S4);
}

void StateToChoiceTester ::
  testS2_to_S3()
{
    this->m_comp.m_smStateStateToChoice_actionHistory.clear();
    this->m_comp.init(StateToChoice::queueDepth, StateToChoice::instanceId);
    this->m_comp.m_smStateStateToChoice_actionHistory.clear();
    this->m_comp.smStateStateToChoice_sendSignal_S2_to_S3();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateStateToChoice_getState(), StateToChoice::SmState_StateToChoice::State::S1_S3);
    const FwIndexType expectedSize = 2;
    ASSERT_EQ(this->m_comp.m_smStateStateToChoice_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToChoice_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToChoice_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToChoice::SmState_StateToChoice::Signal::S2_to_S3);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToChoice::ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), StateToChoice::ActionId::ENTER_S3);
}

void StateToChoiceTester ::
  testS2_to_S4()
{
    this->m_comp.m_smStateStateToChoice_actionHistory.clear();
    this->m_comp.m_smStateStateToChoice_guard_g.reset();
    this->m_comp.m_smStateStateToChoice_guard_g.setReturnValue(true);
    this->m_comp.init(StateToChoice::queueDepth, StateToChoice::instanceId);
    this->m_comp.m_smStateStateToChoice_actionHistory.clear();
    this->m_comp.smStateStateToChoice_sendSignal_S1_to_S4();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateStateToChoice_getState(), StateToChoice::SmState_StateToChoice::State::S4_S5);
    const FwIndexType expectedSize = 4;
    ASSERT_EQ(this->m_comp.m_smStateStateToChoice_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToChoice_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToChoice_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToChoice::SmState_StateToChoice::Signal::S1_to_S4);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToChoice::ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), StateToChoice::ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), StateToChoice::ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), StateToChoice::ActionId::ENTER_S4);
}

void StateToChoiceTester ::
  testS3_to_C()
{
    this->m_comp.m_smStateStateToChoice_actionHistory.clear();
    this->m_comp.m_smStateStateToChoice_guard_g.reset();
    this->m_comp.init(StateToChoice::queueDepth, StateToChoice::instanceId);
    {
        this->m_comp.m_smStateStateToChoice_actionHistory.clear();
        this->m_comp.smStateStateToChoice_sendSignal_S2_to_S3();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    }
    {
        this->m_comp.m_smStateStateToChoice_actionHistory.clear();
        this->m_comp.smStateStateToChoice_sendSignal_S1_to_C();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    }
    ASSERT_EQ(this->m_comp.smStateStateToChoice_getState(), StateToChoice::SmState_StateToChoice::State::S4_S6);
    const FwIndexType expectedSize = 4;
    ASSERT_EQ(this->m_comp.m_smStateStateToChoice_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToChoice_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToChoice_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToChoice::SmState_StateToChoice::Signal::S1_to_C);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToChoice::ActionId::EXIT_S3);
    ASSERT_EQ(actions.getItemAt(1), StateToChoice::ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), StateToChoice::ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), StateToChoice::ActionId::ENTER_S4);
}

void StateToChoiceTester ::
  testS3_to_S4()
{
    this->m_comp.m_smStateStateToChoice_actionHistory.clear();
    this->m_comp.m_smStateStateToChoice_guard_g.reset();
    this->m_comp.init(StateToChoice::queueDepth, StateToChoice::instanceId);
    {
        this->m_comp.m_smStateStateToChoice_actionHistory.clear();
        this->m_comp.smStateStateToChoice_sendSignal_S2_to_S3();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    }
    {
        this->m_comp.m_smStateStateToChoice_actionHistory.clear();
        this->m_comp.smStateStateToChoice_sendSignal_S1_to_S4();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    }
    ASSERT_EQ(this->m_comp.smStateStateToChoice_getState(), StateToChoice::SmState_StateToChoice::State::S4_S6);
    const FwIndexType expectedSize = 4;
    ASSERT_EQ(this->m_comp.m_smStateStateToChoice_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToChoice_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToChoice_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToChoice::SmState_StateToChoice::Signal::S1_to_S4);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToChoice::ActionId::EXIT_S3);
    ASSERT_EQ(actions.getItemAt(1), StateToChoice::ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), StateToChoice::ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), StateToChoice::ActionId::ENTER_S4);
}

} // end namespace SmInstanceState

} // end namespace FppTest
