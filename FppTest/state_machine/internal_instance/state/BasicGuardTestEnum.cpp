// ======================================================================
// \title  BasicGuardTestEnum.cpp
// \author bocchino
// \brief  cpp file for BasicGuardTestEnum component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestEnum.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicGuardTestEnum::BasicGuardTestEnum(const char* const compName)
    : BasicGuardTestEnumComponentBase(compName),
      m_smStateBasicGuardTestEnum_action_a_history(),
      m_smStateBasicGuardTestEnum_guard_g() {}

BasicGuardTestEnum::~BasicGuardTestEnum() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicGuardTestEnum::FppTest_SmState_BasicGuardTestEnum_action_a(SmId smId,
                                                                     FppTest_SmState_BasicGuardTestEnum::Signal signal,
                                                                     const SmHarness::TestEnum& value) {
    ASSERT_EQ(smId, SmId::smStateBasicGuardTestEnum);
    this->m_smStateBasicGuardTestEnum_action_a_history.push(signal, value);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool BasicGuardTestEnum::FppTest_SmState_BasicGuardTestEnum_guard_g(SmId smId,
                                                                    FppTest_SmState_BasicGuardTestEnum::Signal signal,
                                                                    const SmHarness::TestEnum& value) const {
    FW_ASSERT(smId == SmId::smStateBasicGuardTestEnum, static_cast<FwAssertArgType>(smId));
    return this->m_smStateBasicGuardTestEnum_guard_g.call(signal, value);
}


}  // namespace SmInstanceState

}  // namespace FppTest
