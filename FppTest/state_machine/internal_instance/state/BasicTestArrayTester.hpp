// ======================================================================
// \title  BasicTestArrayTester.hpp
// \author m-aleem
// \brief  hpp file for BasicTestArrayTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicTestArrayTester_HPP
#define FppTest_SmInstanceState_BasicTestArrayTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicTestArray.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicTestArrayTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicTestArrayTester
    BasicTestArrayTester(
        BasicTestArray& comp //!< The component under test
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
    BasicTestArray& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
