// ======================================================================
// \title  BasicTestAbsTypeTester.hpp
// \author m-aleem
// \brief  hpp file for BasicTestAbsTypeTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicTestAbsTypeTester_HPP
#define FppTest_SmInstanceState_BasicTestAbsTypeTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicTestAbsType.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicTestAbsTypeTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicTestAbsTypeTester
    BasicTestAbsTypeTester(
        BasicTestAbsType& comp //!< The component under test
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
    BasicTestAbsType& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
