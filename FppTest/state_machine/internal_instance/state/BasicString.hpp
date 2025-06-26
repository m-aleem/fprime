// ======================================================================
// \title  BasicString.hpp
// \author bocchino
// \brief  hpp file for BasicString component implementation class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicString_HPP
#define FppTest_SmInstanceState_BasicString_HPP

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicStringComponentAc.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicStringTester;

class BasicString : public BasicStringComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Friend classes
    // ----------------------------------------------------------------------

    //! Friend class for white-box testing
    friend class BasicStringTester;
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    //! The history size
    static constexpr FwSizeType historySize = 10;

    //! The queue depth
    static constexpr FwSizeType queueDepth = 10;

    //! The instance ID
    static constexpr FwEnumStoreType instanceId = 0;

  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct BasicString object
    BasicString(const char* const compName  //!< The component name
    );

    //! Destroy BasicString object
    ~BasicString();

  private:
    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! The type FppTest_SmState_BasicString
    using SmState_BasicString = FppTest_SmState_BasicString;

  private:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine actions
    // ----------------------------------------------------------------------

    //! Implementation for action a of state machine FppTest_SmState_BasicString
    //!
    //! Action a
    void FppTest_SmState_BasicString_action_a(SmId smId,                                  //!< The state machine id
                                              FppTest_SmState_BasicString::Signal signal  //!< The signal
                                              ) override;

    //! Implementation for action b of state machine FppTest_SmState_BasicString
    //!
    //! Action b
    void FppTest_SmState_BasicString_action_b(SmId smId,                                   //!< The state machine id
                                              FppTest_SmState_BasicString::Signal signal,  //!< The signal
                                              const Fw::StringBase& value                  //!< The value
                                              ) override;


  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The history associated with action a of smStateBasicString
    SmHarness::History<SmState_BasicString::Signal, historySize> m_smStateBasicString_action_a_history;

    //! The history associated with action b of smStateBasicString
    SmHarness::SignalValueHistory<SmState_BasicString::Signal, Fw::String, historySize>
        m_smStateBasicString_action_b_history;
};

}  // namespace SmInstanceState

}  // namespace FppTest

#endif
