// ======================================================================
// \title  BasicU32Tester.hpp
// \author m-aleem
// \brief  hpp file for BasicU32Tester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicU32Tester_HPP
#define FppTest_SmInstanceState_BasicU32Tester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicU32.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicU32Tester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicU32Tester
    BasicU32Tester(
        BasicU32& comp //!< The component under test
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
    BasicU32& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
