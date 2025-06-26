// ======================================================================
// \title  StateToChoiceTester.hpp
// \author m-aleem
// \brief  hpp file for StateToChoiceTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_StateToChoiceTester_HPP
#define FppTest_SmInstanceState_StateToChoiceTester_HPP

#include "FppTest/state_machine/internal_instance/state/StateToChoice.hpp"

namespace FppTest {

namespace SmInstanceState {

class StateToChoiceTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object StateToChoiceTester
    StateToChoiceTester(
        StateToChoice& comp //!< The component under test
    );

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test initial transition
    void testInit();

    //! Test transition S2 to C
    void testS2_to_C();

    //! Test transition S2 to S3
    void testS2_to_S3();

    //! Test transition S2 to S4
    void testS2_to_S4();

    //! Test transition S3 to C
    void testS3_to_C();

    //! Test transition S3 to S4
    void testS3_to_S4();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    StateToChoice& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
