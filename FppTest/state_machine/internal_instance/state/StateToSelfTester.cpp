// ======================================================================
// \title  StateToSelfTester.cpp
// \author m-aleem
// \brief  cpp file for StateToSelfTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/StateToSelfTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

StateToSelfTester ::
  StateToSelfTester(
      StateToSelf& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void StateToSelfTester ::
  testInit()
{
    this->m_comp.m_smStateStateToSelf_actionHistory.clear();
    this->m_comp.init(StateToSelf::queueDepth, StateToSelf::instanceId);
    ASSERT_EQ(this->m_comp.smStateStateToSelf_getState(), StateToSelf::SmState_StateToSelf::State::S1_S2);
    const FwIndexType expectedSize = 2;
    ASSERT_EQ(this->m_comp.m_smStateStateToSelf_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToSelf_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToSelf_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToSelf::SmState_StateToSelf::Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToSelf::ActionId::ENTER_S1);
    ASSERT_EQ(actions.getItemAt(1), StateToSelf::ActionId::ENTER_S2);
}

void StateToSelfTester ::
  testS2_to_S1()
{
    this->m_comp.m_smStateStateToSelf_actionHistory.clear();
    this->m_comp.init(StateToSelf::queueDepth, StateToSelf::instanceId);
    this->m_comp.m_smStateStateToSelf_actionHistory.clear();
    this->m_comp.smStateStateToSelf_sendSignal_S1_to_S1();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateStateToSelf_getState(), StateToSelf::SmState_StateToSelf::State::S1_S2);
    const FwIndexType expectedSize = 5;
    ASSERT_EQ(this->m_comp.m_smStateStateToSelf_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToSelf_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToSelf_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToSelf::SmState_StateToSelf::Signal::S1_to_S1);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToSelf::ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), StateToSelf::ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), StateToSelf::ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), StateToSelf::ActionId::ENTER_S1);
    ASSERT_EQ(actions.getItemAt(4), StateToSelf::ActionId::ENTER_S2);
}

void StateToSelfTester ::
  testS2_to_S3()
{
    this->m_comp.m_smStateStateToSelf_actionHistory.clear();
    this->m_comp.init(StateToSelf::queueDepth, StateToSelf::instanceId);
    this->m_comp.m_smStateStateToSelf_actionHistory.clear();
    this->m_comp.smStateStateToSelf_sendSignal_S2_to_S3();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateStateToSelf_getState(), StateToSelf::SmState_StateToSelf::State::S1_S3);
    const FwIndexType expectedSize = 2;
    ASSERT_EQ(this->m_comp.m_smStateStateToSelf_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToSelf_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToSelf_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToSelf::SmState_StateToSelf::Signal::S2_to_S3);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToSelf::ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), StateToSelf::ActionId::ENTER_S3);
}

void StateToSelfTester ::
  testS3_to_S1()
{
    this->m_comp.m_smStateStateToSelf_actionHistory.clear();
    this->m_comp.init(StateToSelf::queueDepth, StateToSelf::instanceId);
    {
        this->m_comp.m_smStateStateToSelf_actionHistory.clear();
        this->m_comp.smStateStateToSelf_sendSignal_S2_to_S3();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    }
    {
        this->m_comp.m_smStateStateToSelf_actionHistory.clear();
        this->m_comp.smStateStateToSelf_sendSignal_S1_to_S1();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    }
    ASSERT_EQ(this->m_comp.smStateStateToSelf_getState(), StateToSelf::SmState_StateToSelf::State::S1_S2);
    const FwIndexType expectedSize = 5;
    ASSERT_EQ(this->m_comp.m_smStateStateToSelf_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_comp.m_smStateStateToSelf_actionHistory.getSignals();
    const auto& actions = this->m_comp.m_smStateStateToSelf_actionHistory.getValues();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), StateToSelf::SmState_StateToSelf::Signal::S1_to_S1);
    }
    ASSERT_EQ(actions.getItemAt(0), StateToSelf::ActionId::EXIT_S3);
    ASSERT_EQ(actions.getItemAt(1), StateToSelf::ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), StateToSelf::ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), StateToSelf::ActionId::ENTER_S1);
    ASSERT_EQ(actions.getItemAt(4), StateToSelf::ActionId::ENTER_S2);
}

} // end namespace SmInstanceState

} // end namespace FppTest
