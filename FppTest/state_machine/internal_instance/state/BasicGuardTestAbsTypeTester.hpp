// ======================================================================
// \title  BasicGuardTestAbsTypeTester.hpp
// \author m-aleem
// \brief  hpp file for BasicGuardTestAbsTypeTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicGuardTestAbsTypeTester_HPP
#define FppTest_SmInstanceState_BasicGuardTestAbsTypeTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestAbsType.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicGuardTestAbsTypeTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicGuardTestAbsTypeTester
    BasicGuardTestAbsTypeTester(
        BasicGuardTestAbsType& comp //!< The component under test
    );

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test with false guard
    void testFalse();

    //! Test with true guard
    void testTrue();

    //! Test with overflow
    void testOverflow();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    BasicGuardTestAbsType& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
