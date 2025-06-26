// ======================================================================
// \title  StateToSelfTester.hpp
// \author m-aleem
// \brief  hpp file for StateToSelfTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_StateToSelfTester_HPP
#define FppTest_SmInstanceState_StateToSelfTester_HPP

#include "FppTest/state_machine/internal_instance/state/StateToSelf.hpp"

namespace FppTest {

namespace SmInstanceState {

class StateToSelfTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object StateToSelfTester
    StateToSelfTester(
        StateToSelf& comp //!< The component under test
    );

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test initial transition
    void testInit();

    //! Test transition S2 to S1
    void testS2_to_S1();

    //! Test transition S2 to S3
    void testS2_to_S3();

    //! Test transition S3 to S1
    void testS3_to_S1();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    StateToSelf& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
