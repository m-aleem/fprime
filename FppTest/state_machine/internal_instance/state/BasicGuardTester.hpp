#ifndef FPPTEST_STATE_MACHINE_INTERNAL_INSTANCE_STATE_BASICGUARDTESTER_HPP
#define FPPTEST_STATE_MACHINE_INTERNAL_INSTANCE_STATE_BASICGUARDTESTER_HPP

#include "FppTest/state_machine/internal_instance/state/BasicGuard.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicGuardTester {

  public:

    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object BasicGuardTester
    BasicGuardTester(BasicGuard& comp); // Pass by reference

    //! Destroy object BasicGuardTester
    ~BasicGuardTester();

  public:

    // ----------------------------------------------------------------------
    // Public member functions
    // ----------------------------------------------------------------------

    //! Test the state machine with a false guard
    void testFalse();

    //! Test the state machine with a true guard
    void testTrue();

  private:

    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! The component under test
    BasicGuard& m_comp; // Store as a reference

};

}

}

#endif
