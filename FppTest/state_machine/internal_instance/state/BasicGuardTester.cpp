#include "FppTest/state_machine/internal_instance/state/BasicGuardTester.hpp"

#include <gtest/gtest.h>

#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

BasicGuardTester::BasicGuardTester(BasicGuard& comp) : m_comp(comp) {}

BasicGuardTester::~BasicGuardTester() {}

// ----------------------------------------------------------------------
// Public member functions
// ----------------------------------------------------------------------

void BasicGuardTester::testFalse() {
    this->m_comp.m_smStateBasicGuard_action_a_history.clear();
    this->m_comp.m_smStateBasicGuard_guard_g.reset();
    this->m_comp.init(BasicGuard::queueDepth, BasicGuard::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuard_getState(), BasicGuard::SmState_BasicGuard::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuard_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuard_guard_g.getCallHistory().getSize(), 0);
    this->m_comp.smStateBasicGuard_sendSignal_s();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuard_getState(), BasicGuard::SmState_BasicGuard::State::S);
    this->m_comp.checkActionsAndGuards(0, 1);
}

void BasicGuardTester::testTrue() {
    this->m_comp.m_smStateBasicGuard_action_a_history.clear();
    this->m_comp.m_smStateBasicGuard_guard_g.reset();
    this->m_comp.m_smStateBasicGuard_guard_g.setReturnValue(true);
    this->m_comp.init(BasicGuard::queueDepth, BasicGuard::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicGuard_getState(), BasicGuard::SmState_BasicGuard::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuard_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_comp.m_smStateBasicGuard_guard_g.getCallHistory().getSize(), 0);
    this->m_comp.smStateBasicGuard_sendSignal_s();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicGuard_getState(), BasicGuard::SmState_BasicGuard::State::T);
    this->m_comp.checkActionsAndGuards(6, 1);
}

}

}
