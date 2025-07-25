// ======================================================================
// \title  InternalTester.cpp
// \author bocchino
// \brief  cpp file for InternalTester component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/InternalTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

InternalTester::InternalTester(const char* const compName)
    : InternalComponentBase(compName), m_smStateInternal_action_a_history() {}

InternalTester::~InternalTester() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void InternalTester::FppTest_SmState_Internal_action_a(SmId smId, FppTest_SmState_Internal::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateInternal);
    this->m_smStateInternal_action_a_history.push(signal);
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void InternalTester::testInit() {
    this->m_smStateInternal_action_a_history.clear();
    this->init(queueDepth, instanceId);
    ASSERT_EQ(smStateInternal_getState(), SmState_Internal::State::S1_S2);
    ASSERT_EQ(this->m_smStateInternal_action_a_history.getSize(), 0);
}

void InternalTester::testS2_internal() {
    this->m_smStateInternal_action_a_history.clear();
    this->init(queueDepth, instanceId);
    ASSERT_EQ(smStateInternal_getState(), SmState_Internal::State::S1_S2);
    this->smStateInternal_sendSignal_S1_internal();
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_EQ(smStateInternal_getState(), SmState_Internal::State::S1_S2);
    ASSERT_EQ(this->m_smStateInternal_action_a_history.getSize(), 1);
    ASSERT_EQ(this->m_smStateInternal_action_a_history.getItemAt(0), SmState_Internal::Signal::S1_internal);
}

void InternalTester::testS2_to_S3() {
    this->m_smStateInternal_action_a_history.clear();
    this->init(queueDepth, instanceId);
    ASSERT_EQ(smStateInternal_getState(), SmState_Internal::State::S1_S2);
    this->smStateInternal_sendSignal_S2_to_S3();
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_EQ(smStateInternal_getState(), SmState_Internal::State::S1_S3);
    ASSERT_EQ(this->m_smStateInternal_action_a_history.getSize(), 0);
}

void InternalTester::testS3_internal() {
    this->m_smStateInternal_action_a_history.clear();
    this->init(queueDepth, instanceId);
    ASSERT_EQ(smStateInternal_getState(), SmState_Internal::State::S1_S2);
    {
        this->smStateInternal_sendSignal_S2_to_S3();
        const auto status = this->doDispatch();
        ASSERT_EQ(status, MSG_DISPATCH_OK);
        ASSERT_EQ(smStateInternal_getState(), SmState_Internal::State::S1_S3);
    }
    {
        this->smStateInternal_sendSignal_S1_internal();
        const auto status = this->doDispatch();
        ASSERT_EQ(status, MSG_DISPATCH_OK);
        ASSERT_EQ(smStateInternal_getState(), SmState_Internal::State::S1_S3);
        ASSERT_EQ(this->m_smStateInternal_action_a_history.getSize(), 1);
        ASSERT_EQ(this->m_smStateInternal_action_a_history.getItemAt(0), SmState_Internal::Signal::S1_internal);
    }
}

}  // namespace SmInstanceState

}  // namespace FppTest
