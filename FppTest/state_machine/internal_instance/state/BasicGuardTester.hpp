// \title  BasicGuardTester.hpp
// \author m-aleem
// \brief  hpp file for BasicGuardTester class


#ifndef FppTest_SmInstanceState_BasicGuardTester_HPP
#define FppTest_SmInstanceState_BasicGuardTester_HPP

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

} // end namespace SmInstanceState

} // end namespace FppTest

#endif