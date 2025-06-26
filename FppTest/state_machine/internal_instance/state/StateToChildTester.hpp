// ======================================================================
// \title  StateToChildTester.hpp
// \author m-aleem
// \brief  hpp file for StateToChildTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_StateToChildTester_HPP
#define FppTest_SmInstanceState_StateToChildTester_HPP

#include "FppTest/state_machine/internal_instance/state/StateToChild.hpp"

namespace FppTest {

namespace SmInstanceState {

class StateToChildTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object StateToChildTester
    StateToChildTester(
        StateToChild& comp //!< The component under test
    );

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test initial transition
    void testInit();

    //! Test transition from S2 to S2
    void testS2_to_S2();

    //! Test transition from S2 to S3
    void testS2_to_S3();

    //! Test transition from S3 to S2
    void testS3_to_S2();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    StateToChild& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
