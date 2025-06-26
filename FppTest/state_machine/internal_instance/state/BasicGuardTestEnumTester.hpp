// ======================================================================
// \title  BasicGuardTestEnumTester.hpp
// \author m-aleem
// \brief  hpp file for BasicGuardTestEnumTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicGuardTestEnumTester_HPP
#define FppTest_SmInstanceState_BasicGuardTestEnumTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestEnum.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicGuardTestEnumTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicGuardTestEnumTester
    BasicGuardTestEnumTester(
        BasicGuardTestEnum& comp //!< The component under test
    );

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test with true guard
    void testTrue();

    //! Test with false guard
    void testFalse();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    BasicGuardTestEnum& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
