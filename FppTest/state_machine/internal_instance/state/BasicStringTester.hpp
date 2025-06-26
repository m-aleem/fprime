// ======================================================================
// \title  BasicStringTester.hpp
// \author m-aleem
// \brief  hpp file for BasicStringTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicStringTester_HPP
#define FppTest_SmInstanceState_BasicStringTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicString.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicStringTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicStringTester
    BasicStringTester(
        BasicString& comp //!< The component under test
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
    BasicString& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
