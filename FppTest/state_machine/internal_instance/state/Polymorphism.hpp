// ======================================================================
// \title  Polymorphism.hpp
// \author bocchino
// \brief  hpp file for Polymorphism component implementation class
// ======================================================================

#ifndef FppTest_SmInstanceState_Polymorphism_HPP
#define FppTest_SmInstanceState_Polymorphism_HPP

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal_instance/state/PolymorphismComponentAc.hpp"

namespace FppTest {

namespace SmInstanceState {

class PolymorphismTester;

class Polymorphism : public PolymorphismComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Friend classes
    // ----------------------------------------------------------------------

    //! Friend class for white-box testing
    friend class PolymorphismTester;
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    //! The queue depth
    static constexpr FwSizeType queueDepth = 10;

    //! The instance ID
    static constexpr FwEnumStoreType instanceId = 0;

  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Polymorphism object
    Polymorphism(const char* const compName  //!< The component name
    );

    //! Destroy Polymorphism object
    ~Polymorphism();

  private:
    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! The type FppTest_SmState_Polymorphism
    using SmState_Polymorphism = FppTest_SmState_Polymorphism;

};

}  // namespace SmInstanceState

}  // namespace FppTest

#endif
