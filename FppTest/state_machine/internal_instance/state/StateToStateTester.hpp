// ======================================================================
// \title  StateToStateTester.hpp
// \author m-aleem
// \brief  hpp file for StateToStateTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_StateToStateTester_HPP
#define FppTest_SmInstanceState_StateToStateTester_HPP

#include "FppTest/state_machine/internal_instance/state/StateToState.hpp"

namespace FppTest {

namespace SmInstanceState {

class StateToStateTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object StateToStateTester
    StateToStateTester(
        StateToState& comp //!< The component under test
    );

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test initial transition
    void testInit();

    //! Test transition S2 to S3
    void testS2_to_S3();

    //! Test transition S2 to S4
    void testS2_to_S4();

    //! Test transition S2 to S5
    void testS2_to_S5();

    //! Test transition S3 to S4
    void testS3_to_S4();

    //! Test transition S3 to S5
    void testS3_to_S5();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    StateToState& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
