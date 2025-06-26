// ======================================================================
// \title  BasicSelfTester.hpp
// \author m-aleem
// \brief  hpp file for BasicSelfTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicSelfTester_HPP
#define FppTest_SmInstanceState_BasicSelfTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicSelf.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicSelfTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicSelfTester
    BasicSelfTester(
        BasicSelf& comp //!< The component under test
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
    BasicSelf& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
