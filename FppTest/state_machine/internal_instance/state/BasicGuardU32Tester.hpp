// ======================================================================
// \title  BasicGuardU32Tester.hpp
// \author m-aleem
// \brief  hpp file for BasicGuardU32Tester class
// ======================================================================

#ifndef FppTest_SmInstanceState_BasicGuardU32Tester_HPP
#define FppTest_SmInstanceState_BasicGuardU32Tester_HPP

#include "FppTest/state_machine/internal_instance/state/BasicGuardU32.hpp"

namespace FppTest {

namespace SmInstanceState {

class BasicGuardU32Tester {

  public:
    // ----------------------------------------------------------------------
    // Construction
    // ----------------------------------------------------------------------

    //! Construct object BasicGuardU32Tester
    BasicGuardU32Tester(
        BasicGuardU32& comp //!< The component under test
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
    BasicGuardU32& m_comp;

};

} // end namespace SmInstanceState

} // end namespace FppTest

#endif
