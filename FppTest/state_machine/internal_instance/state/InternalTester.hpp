// ======================================================================
// \title  InternalTester.hpp
// \author m-aleem
// \brief  hpp file for InternalTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_InternalTester_HPP
#define FppTest_SmInstanceState_InternalTester_HPP

#include "FppTest/state_machine/internal_instance/state/Internal.hpp"

namespace FppTest {

namespace SmInstanceState {

class InternalTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object InternalTester
    InternalTester(
        Internal& comp //!< The component under test
    );

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test initial transition
    void testInit();

    //! Test internal transition in S2
    void testS2_internal();

    //! Test transition S2 to S3
    void testS2_to_S3();

    //! Test internal transition in S3
    void testS3_internal();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    Internal& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
