// ======================================================================
// \title  BasicInternalTester.hpp
// \author m-aleem
// \brief  hpp file for BasicInternalTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicInternalTester_HPP
#define FppTest_SmInstanceState_BasicInternalTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicInternal.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicInternalTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicInternalTester
    BasicInternalTester(
        BasicInternal& comp //!< The component under test
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
    BasicInternal& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
