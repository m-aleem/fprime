// ======================================================================
// \title  PolymorphismTester.hpp
// \author m-aleem
// \brief  hpp file for PolymorphismTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_PolymorphismTester_HPP
#define FppTest_SmInstanceState_PolymorphismTester_HPP

#include "FppTest/state_machine/internal_instance/state/Polymorphism.hpp"

namespace FppTest {

namespace SmInstanceState {

class PolymorphismTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object PolymorphismTester
    PolymorphismTester(
        Polymorphism& comp //!< The component under test
    );

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test initial transition
    void testInit();

    //! Test polymorphic transition in S2
    void testS2_poly();

    //! Test transition from S2 to S3
    void testS2_to_S3();

    //! Test polymorphic transition in S3
    void testS3_poly();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    Polymorphism& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
