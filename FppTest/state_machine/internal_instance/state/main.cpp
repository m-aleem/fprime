// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/Basic.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuard.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardString.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardStringTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestAbsType.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestAbsTypeTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestArray.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestArrayTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestEnum.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestEnumTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestStruct.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestStructTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardU32.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardU32Tester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicInternal.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicInternalTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicSelf.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicSelfTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicString.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicStringTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicTestAbsType.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicTestAbsTypeTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicTestArray.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicTestArrayTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicTestEnum.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicTestEnumTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicTestStruct.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicTestStructTester.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicU32.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicU32Tester.hpp"
#include "FppTest/state_machine/internal_instance/state/Internal.hpp"
#include "FppTest/state_machine/internal_instance/state/InternalTester.hpp"
#include "FppTest/state_machine/internal_instance/state/Polymorphism.hpp"
#include "FppTest/state_machine/internal_instance/state/PolymorphismTester.hpp"
#include "FppTest/state_machine/internal_instance/state/StateToChild.hpp"
#include "FppTest/state_machine/internal_instance/state/StateToChildTester.hpp"
#include "FppTest/state_machine/internal_instance/state/StateToChoice.hpp"
#include "FppTest/state_machine/internal_instance/state/StateToChoiceTester.hpp"
#include "FppTest/state_machine/internal_instance/state/StateToSelf.hpp"
#include "FppTest/state_machine/internal_instance/state/StateToSelfTester.hpp"
#include "FppTest/state_machine/internal_instance/state/StateToState.hpp"
#include "FppTest/state_machine/internal_instance/state/StateToStateTester.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, Test) {
    FppTest::SmInstanceState::Basic basic("basic");
    FppTest::SmInstanceState::BasicTester tester(basic);
    tester.test();
}

TEST(BasicGuard, False) {
    FppTest::SmInstanceState::BasicGuard basicGuard("basicGuard");
    FppTest::SmInstanceState::BasicGuardTester tester(basicGuard);
    tester.testFalse();
}

TEST(BasicGuard, True) {
    FppTest::SmInstanceState::BasicGuard basicGuard("basicGuard");
    FppTest::SmInstanceState::BasicGuardTester tester(basicGuard);
    tester.testTrue();
}

TEST(BasicGuardString, False) {
    FppTest::SmInstanceState::BasicGuardString basicGuardString("basicGuardString");
    FppTest::SmInstanceState::BasicGuardStringTester tester(basicGuardString);
    tester.testFalse();
}

TEST(BasicGuardString, True) {
    FppTest::SmInstanceState::BasicGuardString basicGuardString("basicGuardString");
    FppTest::SmInstanceState::BasicGuardStringTester tester(basicGuardString);
    tester.testTrue();
}

TEST(BasicGuardTestAbsType, False) {
    FppTest::SmInstanceState::BasicGuardTestAbsType basicGuardTestAbsType("basicGuardTestAbsType");
    FppTest::SmInstanceState::BasicGuardTestAbsTypeTester tester(basicGuardTestAbsType);
    tester.testFalse();
}

TEST(BasicGuardTestAbsType, Overflow) {
    FppTest::SmInstanceState::BasicGuardTestAbsType basicGuardTestAbsType("basicGuardTestAbsType");
    FppTest::SmInstanceState::BasicGuardTestAbsTypeTester tester(basicGuardTestAbsType);
    tester.testOverflow();
}

TEST(BasicGuardTestAbsType, True) {
    FppTest::SmInstanceState::BasicGuardTestAbsType basicGuardTestAbsType("basicGuardTestAbsType");
    FppTest::SmInstanceState::BasicGuardTestAbsTypeTester tester(basicGuardTestAbsType);
    tester.testTrue();
}

TEST(BasicGuardTestArray, False) {
    FppTest::SmInstanceState::BasicGuardTestArray basicGuardTestArray("basicGuardTestArray");
    FppTest::SmInstanceState::BasicGuardTestArrayTester tester(basicGuardTestArray);
    tester.testFalse();
}

TEST(BasicGuardTestArray, True) {
    FppTest::SmInstanceState::BasicGuardTestArray basicGuardTestArray("basicGuardTestArray");
    FppTest::SmInstanceState::BasicGuardTestArrayTester tester(basicGuardTestArray);
    tester.testTrue();
}

TEST(BasicGuardTestEnum, False) {
    FppTest::SmInstanceState::BasicGuardTestEnum basicGuardTestEnum("basicGuardTestEnum");
    FppTest::SmInstanceState::BasicGuardTestEnumTester tester(basicGuardTestEnum);
    tester.testFalse();
}

TEST(BasicGuardTestEnum, True) {
    FppTest::SmInstanceState::BasicGuardTestEnum basicGuardTestEnum("basicGuardTestEnum");
    FppTest::SmInstanceState::BasicGuardTestEnumTester tester(basicGuardTestEnum);
    tester.testTrue();
}

TEST(BasicGuardTestStruct, False) {
    FppTest::SmInstanceState::BasicGuardTestStruct basicGuardTestStruct("basicGuardTestStruct");
    FppTest::SmInstanceState::BasicGuardTestStructTester tester(basicGuardTestStruct);
    tester.testFalse();
}

TEST(BasicGuardTestStruct, True) {
    FppTest::SmInstanceState::BasicGuardTestStruct basicGuardTestStruct("basicGuardTestStruct");
    FppTest::SmInstanceState::BasicGuardTestStructTester tester(basicGuardTestStruct);
    tester.testTrue();
}

TEST(BasicGuardU32, False) {
    FppTest::SmInstanceState::BasicGuardU32 basicGuardU32("basicGuardU32");
    FppTest::SmInstanceState::BasicGuardU32Tester tester(basicGuardU32);
    tester.testFalse();
}

TEST(BasicGuardU32, True) {
    FppTest::SmInstanceState::BasicGuardU32 basicGuardU32("basicGuardU32");
    FppTest::SmInstanceState::BasicGuardU32Tester tester(basicGuardU32);
    tester.testTrue();
}

TEST(BasicInternal, Test) {
    FppTest::SmInstanceState::BasicInternal basicInternal("basicInternal");
    FppTest::SmInstanceState::BasicInternalTester tester(basicInternal);
    tester.test();
}

TEST(BasicSelf, Test) {
    FppTest::SmInstanceState::BasicSelf basicSelf("basicSelf");
    FppTest::SmInstanceState::BasicSelfTester tester(basicSelf);
    tester.test();
}

TEST(BasicString, Test) {
    FppTest::SmInstanceState::BasicString basicString("basicString");
    FppTest::SmInstanceState::BasicStringTester tester(basicString);
    tester.test();
}

TEST(BasicTestAbsType, Test) {
    FppTest::SmInstanceState::BasicTestAbsType basicTestAbsType("basicTestAbsType");
    FppTest::SmInstanceState::BasicTestAbsTypeTester tester(basicTestAbsType);
    tester.test();
}

TEST(BasicTestArray, Test) {
    FppTest::SmInstanceState::BasicTestArray basicTestArray("basicTestArray");
    FppTest::SmInstanceState::BasicTestArrayTester tester(basicTestArray);
    tester.test();
}

TEST(BasicTestEnum, Test) {
    FppTest::SmInstanceState::BasicTestEnum basicTestEnum("basicTestEnum");
    FppTest::SmInstanceState::BasicTestEnumTester tester(basicTestEnum);
    tester.test();
}

TEST(BasicTestStruct, Test) {
    FppTest::SmInstanceState::BasicTestStruct basicTestStruct("basicTestStruct");
    FppTest::SmInstanceState::BasicTestStructTester tester(basicTestStruct);
    tester.test();
}

TEST(BasicU32, Test) {
    FppTest::SmInstanceState::BasicU32 basicU32("basicU32");
    FppTest::SmInstanceState::BasicU32Tester tester(basicU32);
    tester.test();
}

TEST(Internal, Init) {
    FppTest::SmInstanceState::Internal internal("internal");
    FppTest::SmInstanceState::InternalTester tester(internal);
    tester.testInit();
}

TEST(Internal, S2_internal) {
    FppTest::SmInstanceState::Internal internal("internal");
    FppTest::SmInstanceState::InternalTester tester(internal);
    tester.testS2_internal();
}

TEST(Internal, S2_to_S3) {
    FppTest::SmInstanceState::Internal internal("internal");
    FppTest::SmInstanceState::InternalTester tester(internal);
    tester.testS2_to_S3();
}

TEST(Internal, S3_internal) {
    FppTest::SmInstanceState::Internal internal("internal");
    FppTest::SmInstanceState::InternalTester tester(internal);
    tester.testS3_internal();
}

TEST(Polymorphism, Init) {
    FppTest::SmInstanceState::Polymorphism polymorphism("polymorphism");
    FppTest::SmInstanceState::PolymorphismTester tester(polymorphism);
    tester.testInit();
}

TEST(Polymorphism, S2_poly) {
    FppTest::SmInstanceState::Polymorphism polymorphism("polymorphism");
    FppTest::SmInstanceState::PolymorphismTester tester(polymorphism);
    tester.testS2_poly();
}

TEST(Polymorphism, S2_to_S3) {
    FppTest::SmInstanceState::Polymorphism polymorphism("polymorphism");
    FppTest::SmInstanceState::PolymorphismTester tester(polymorphism);
    tester.testS2_to_S3();
}

TEST(Polymorphism, S3_poly) {
    FppTest::SmInstanceState::Polymorphism polymorphism("polymorphism");
    FppTest::SmInstanceState::PolymorphismTester tester(polymorphism);
    tester.testS3_poly();
}

TEST(StateToChild, Init) {
    FppTest::SmInstanceState::StateToChild stateToChild("stateToChild");
    FppTest::SmInstanceState::StateToChildTester tester(stateToChild);
    tester.testInit();
}

TEST(StateToChild, S2_to_S2) {
    FppTest::SmInstanceState::StateToChild stateToChild("stateToChild");
    FppTest::SmInstanceState::StateToChildTester tester(stateToChild);
    tester.testS2_to_S2();
}

TEST(StateToChild, S2_to_S3) {
    FppTest::SmInstanceState::StateToChild stateToChild("stateToChild");
    FppTest::SmInstanceState::StateToChildTester tester(stateToChild);
    tester.testS2_to_S3();
}

TEST(StateToChild, S3_to_S2) {
    FppTest::SmInstanceState::StateToChild stateToChild("stateToChild");
    FppTest::SmInstanceState::StateToChildTester tester(stateToChild);
    tester.testS3_to_S2();
}

TEST(StateToChoice, Init) {
    FppTest::SmInstanceState::StateToChoice stateToChoice("stateToChoice");
    FppTest::SmInstanceState::StateToChoiceTester tester(stateToChoice);
    tester.testInit();
}

TEST(StateToChoice, S2_to_C) {
    FppTest::SmInstanceState::StateToChoice stateToChoice("stateToChoice");
    FppTest::SmInstanceState::StateToChoiceTester tester(stateToChoice);
    tester.testS2_to_C();
}

TEST(StateToChoice, S2_to_S3) {
    FppTest::SmInstanceState::StateToChoice stateToChoice("stateToChoice");
    FppTest::SmInstanceState::StateToChoiceTester tester(stateToChoice);
    tester.testS2_to_S3();
}

TEST(StateToChoice, S2_to_S4) {
    FppTest::SmInstanceState::StateToChoice stateToChoice("stateToChoice");
    FppTest::SmInstanceState::StateToChoiceTester tester(stateToChoice);
    tester.testS2_to_S4();
}

TEST(StateToChoice, S3_to_C) {
    FppTest::SmInstanceState::StateToChoice stateToChoice("stateToChoice");
    FppTest::SmInstanceState::StateToChoiceTester tester(stateToChoice);
    tester.testS3_to_C();
}

TEST(StateToChoice, S3_to_S4) {
    FppTest::SmInstanceState::StateToChoice stateToChoice("stateToChoice");
    FppTest::SmInstanceState::StateToChoiceTester tester(stateToChoice);
    tester.testS3_to_S4();
}

TEST(StateToSelf, Init) {
    FppTest::SmInstanceState::StateToSelf stateToSelf("stateToSelf");
    FppTest::SmInstanceState::StateToSelfTester tester(stateToSelf);
    tester.testInit();
}

TEST(StateToSelf, S2_to_S1) {
    FppTest::SmInstanceState::StateToSelf stateToSelf("stateToSelf");
    FppTest::SmInstanceState::StateToSelfTester tester(stateToSelf);
    tester.testS2_to_S1();
}

TEST(StateToSelf, S2_to_S3) {
    FppTest::SmInstanceState::StateToSelf stateToSelf("stateToSelf");
    FppTest::SmInstanceState::StateToSelfTester tester(stateToSelf);
    tester.testS2_to_S3();
}

TEST(StateToSelf, S3_to_S1) {
    FppTest::SmInstanceState::StateToSelf stateToSelf("stateToSelf");
    FppTest::SmInstanceState::StateToSelfTester tester(stateToSelf);
    tester.testS3_to_S1();
}

TEST(StateToState, Init) {
    FppTest::SmInstanceState::StateToState stateToState("stateToState");
    FppTest::SmInstanceState::StateToStateTester tester(stateToState);
    tester.testInit();
}

TEST(StateToState, S2_to_S3) {
    FppTest::SmInstanceState::StateToState stateToState("stateToState");
    FppTest::SmInstanceState::StateToStateTester tester(stateToState);
    tester.testS2_to_S3();
}

TEST(StateToState, S2_to_S4) {
    FppTest::SmInstanceState::StateToState stateToState("stateToState");
    FppTest::SmInstanceState::StateToStateTester tester(stateToState);
    tester.testS2_to_S4();
}

TEST(StateToState, S2_to_S5) {
    FppTest::SmInstanceState::StateToState stateToState("stateToState");
    FppTest::SmInstanceState::StateToStateTester tester(stateToState);
    tester.testS2_to_S5();
}

TEST(StateToState, S3_to_S4) {
    FppTest::SmInstanceState::StateToState stateToState("stateToState");
    FppTest::SmInstanceState::StateToStateTester tester(stateToState);
    tester.testS3_to_S4();
}

TEST(StateToState, S3_to_S5) {
    FppTest::SmInstanceState::StateToState stateToState("stateToState");
    FppTest::SmInstanceState::StateToStateTester tester(stateToState);
    tester.testS3_to_S5();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
