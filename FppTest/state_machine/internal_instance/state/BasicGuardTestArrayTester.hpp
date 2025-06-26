// ======================================================================
// \title  BasicGuardTestArrayTester.hpp
// \author m-aleem
// \brief  hpp file for BasicGuardTestArrayTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicGuardTestArrayTester_HPP
#define FppTest_SmInstanceState_BasicGuardTestArrayTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestArray.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicGuardTestArrayTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicGuardTestArrayTester
    BasicGuardTestArrayTester(
        BasicGuardTestArray& comp //!< The component under test
    );

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test with true guard
    void testTrue();

    //! Test with false guard
    void testFalse();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    BasicGuardTestArray& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
