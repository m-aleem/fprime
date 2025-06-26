// ======================================================================
// \title  BasicSelfTester.cpp
// \author m-aleem
// \brief  cpp file for BasicSelfTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicSelfTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

BasicSelfTester ::
  BasicSelfTester(
      BasicSelf& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicSelfTester ::
  test()
{
    this->m_comp.m_smStateBasicSelf_action_a_history.clear();
    this->m_comp.init(BasicSelf::queueDepth, BasicSelf::instanceId);
    ASSERT_EQ(this->m_comp.smStateBasicSelf_getState(), BasicSelf::SmState_BasicSelf::State::S);
    ASSERT_EQ(this->m_comp.m_smStateBasicSelf_action_a_history.getSize(), 1);
    ASSERT_EQ(this->m_comp.m_smStateBasicSelf_action_a_history.getItemAt(0),
              BasicSelf::SmState_BasicSelf::Signal::__FPRIME_AC_INITIAL_TRANSITION);
    this->m_comp.m_smStateBasicSelf_action_a_history.clear();
    this->m_comp.smStateBasicSelf_sendSignal_s();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStateBasicSelf_getState(), BasicSelf::SmState_BasicSelf::State::S);
    const FwIndexType expectedSize = 6;
    ASSERT_EQ(this->m_comp.m_smStateBasicSelf_action_a_history.getSize(), expectedSize);
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(this->m_comp.m_smStateBasicSelf_action_a_history.getItemAt(i), BasicSelf::SmState_BasicSelf::Signal::s);
    }
}

} // end namespace SmInstanceState

} // end namespace FppTest
