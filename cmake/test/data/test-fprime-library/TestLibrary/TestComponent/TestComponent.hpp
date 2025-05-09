#ifndef TestLibrary_TestComponent_HPP
#define TestLibrary_TestComponent_HPP

#include <TestLibrary/TestComponent/TestComponentComponentAc.hpp>

namespace TestLibrary {

class TestComponent : public TestComponentComponentBase
{
  public:
    TestComponent(const char* name);
    ~TestComponent();
  private:
    void schedIn_handler(FwIndexType portNum, U32 context);
};

};
#endif
