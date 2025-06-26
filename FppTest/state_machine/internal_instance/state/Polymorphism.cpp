// ======================================================================
// \title  Polymorphism.cpp
// \author bocchino
// \brief  cpp file for Polymorphism component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/Polymorphism.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Polymorphism::Polymorphism(const char* const compName) : PolymorphismComponentBase(compName) {}

Polymorphism::~Polymorphism() {}


}  // namespace SmInstanceState

}  // namespace FppTest
