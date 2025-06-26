// ======================================================================
// \title  BasicTestEnumTester.hpp
// \author m-aleem
// \brief  hpp file for BasicTestEnumTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicTestEnumTester_HPP
#define FppTest_SmInstanceState_BasicTestEnumTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicTestEnum.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicTestEnumTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicTestEnumTester
    BasicTestEnumTester(
        BasicTestEnum& comp //!< The component under test
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
    BasicTestEnum& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
