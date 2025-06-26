// ======================================================================
// \title  BasicTestStructTester.hpp
// \author m-aleem
// \brief  hpp file for BasicTestStructTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicTestStructTester_HPP
#define FppTest_SmInstanceState_BasicTestStructTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicTestStruct.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicTestStructTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicTestStructTester
    BasicTestStructTester(
        BasicTestStruct& comp //!< The component under test
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
    BasicTestStruct& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
