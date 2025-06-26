// ======================================================================
// \title  BasicGuardU32.cpp
// \author bocchino
// \brief  cpp file for BasicGuardU32 component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicGuardU32.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicGuardU32::BasicGuardU32(const char* const compName)
    : BasicGuardU32ComponentBase(compName),
      m_smStateBasicGuardU32_action_a_history(),
      m_smStateBasicGuardU32_guard_g() {}

BasicGuardU32::~BasicGuardU32() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicGuardU32::FppTest_SmState_BasicGuardU32_action_a(SmId smId,
                                                           FppTest_SmState_BasicGuardU32::Signal signal,
                                                           U32 value) {
    ASSERT_EQ(smId, SmId::smStateBasicGuardU32);
    this->m_smStateBasicGuardU32_action_a_history.push(signal, value);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool BasicGuardU32::FppTest_SmState_BasicGuardU32_guard_g(SmId smId,
                                                          FppTest_SmState_BasicGuardU32::Signal signal,
                                                          U32 value) const {
    FW_ASSERT(smId == SmId::smStateBasicGuardU32, static_cast<FwAssertArgType>(smId));
    return this->m_smStateBasicGuardU32_guard_g.call(signal, value);
}


}  // namespace SmInstanceState

}  // namespace FppTest
