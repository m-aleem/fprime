// ======================================================================
// \title  BasicGuardStringTester.hpp
// \author m-aleem
// \brief  hpp file for BasicGuardStringTester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicGuardStringTester_HPP
#define FppTest_SmInstanceState_BasicGuardStringTester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicGuardString.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicGuardStringTester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicGuardStringTester
    BasicGuardStringTester(
        BasicGuardString& comp //!< The component under test
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
    BasicGuardString& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
