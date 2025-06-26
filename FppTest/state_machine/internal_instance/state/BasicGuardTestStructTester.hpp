// ======================================================================
// \title  BasicGuardTestStructTester.hpp
// \author m-aleem
// \brief  hpp file for BasicGuardTestStructTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicGuardTestStructTester_HPP
#define FppTest_SmInstanceState_BasicGuardTestStructTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestStruct.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicGuardTestStructTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicGuardTestStructTester
    BasicGuardTestStructTester(
        BasicGuardTestStruct& comp //!< The component under test
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
    BasicGuardTestStruct& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
