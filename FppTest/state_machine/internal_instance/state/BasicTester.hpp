// ======================================================================
// \title  BasicTester.hpp
// \author m-aleem
// \brief  hpp file for BasicTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicTester_HPP
#define FppTest_SmInstanceState_BasicTester_HPP

#include "FppTest/state_machine/internal_instance/state/Basic.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicTester
    BasicTester(
        Basic& comp //!< The component under test
    );

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Run the test
    void test();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    Basic& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
