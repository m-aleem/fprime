// ======================================================================
// \title  PolymorphismTester.cpp
// \author m-aleem
// \brief  cpp file for PolymorphismTester class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/PolymorphismTester.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Construction
// ----------------------------------------------------------------------

PolymorphismTester ::
  PolymorphismTester(
      Polymorphism& comp
  ) :
    m_comp(comp)
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void PolymorphismTester ::
  testInit()
{
    this->m_comp.init(Polymorphism::queueDepth, Polymorphism::instanceId);
    ASSERT_EQ(this->m_comp.smStatePolymorphism_getState(), Polymorphism::SmState_Polymorphism::State::S1_S2);
}

void PolymorphismTester ::
  testS2_poly()
{
    this->m_comp.init(Polymorphism::queueDepth, Polymorphism::instanceId);
    ASSERT_EQ(this->m_comp.smStatePolymorphism_getState(), Polymorphism::SmState_Polymorphism::State::S1_S2);
    this->m_comp.smStatePolymorphism_sendSignal_poly();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStatePolymorphism_getState(), Polymorphism::SmState_Polymorphism::State::S4);
}

void PolymorphismTester ::
  testS2_to_S3()
{
    this->m_comp.init(Polymorphism::queueDepth, Polymorphism::instanceId);
    ASSERT_EQ(this->m_comp.smStatePolymorphism_getState(), Polymorphism::SmState_Polymorphism::State::S1_S2);
    this->m_comp.smStatePolymorphism_sendSignal_S2_to_S3();
    const auto status = this->m_comp.doDispatch();
    ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_comp.smStatePolymorphism_getState(), Polymorphism::SmState_Polymorphism::State::S1_S3);
}

void PolymorphismTester ::
  testS3_poly()
{
    this->m_comp.init(Polymorphism::queueDepth, Polymorphism::instanceId);
    ASSERT_EQ(this->m_comp.smStatePolymorphism_getState(), Polymorphism::SmState_Polymorphism::State::S1_S2);
    {
        this->m_comp.smStatePolymorphism_sendSignal_S2_to_S3();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
        ASSERT_EQ(this->m_comp.smStatePolymorphism_getState(), Polymorphism::SmState_Polymorphism::State::S1_S3);
    }
    {
        this->m_comp.smStatePolymorphism_sendSignal_poly();
        const auto status = this->m_comp.doDispatch();
        ASSERT_EQ(status, Fw::QueuedComponentBase::MSG_DISPATCH_OK);
        ASSERT_EQ(this->m_comp.smStatePolymorphism_getState(), Polymorphism::SmState_Polymorphism::State::S5);
    }
}

} // end namespace SmInstanceState

} // end namespace FppTest
