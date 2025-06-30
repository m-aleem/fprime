/*
 * TimeTest.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: tcanham
 */

#include <Fw/Time/Time.hpp>
#include <Fw/Time/TimeInterval.hpp>
#include <iostream>
#include <gtest/gtest.h>


namespace Fw {
    class TimeTester{

        public:
            // ----------------------------------------------------------------------
            // Construction and destruction
            // ----------------------------------------------------------------------
            TimeTester()
            {
            }

            ~TimeTester()
            {
            }

            // ----------------------------------------------------------------------
            // Tests
            // ----------------------------------------------------------------------
            void test_MathTest()
            {
                Fw::Time time1;
                Fw::Time time2;

                // Comparison
                time1.set(1000,1000);
                time2.set(1000,1000);
                ASSERT_TRUE(time1 == time2);
                ASSERT_TRUE(time1 >= time2);
                ASSERT_TRUE(time1 <= time2);

                time1.set(1000,1000);
                time2.set(2000,1000);
                ASSERT_TRUE(time1 != time2);
                ASSERT_TRUE(time1 < time2);
                ASSERT_TRUE(time1 <= time2);

                time1.set(2000,1000);
                time2.set(1000,1000);
                ASSERT_TRUE(time1 > time2);
                ASSERT_TRUE(time1 >= time2);

                // Addition
                time1.set(1000,1000);
                time2.set(4000,2000);
                Fw::Time time_sum = Fw::Time::add(time1,time2);
                ASSERT_EQ(time_sum.m_seconds,5000);
                ASSERT_EQ(time_sum.m_useconds,3000);

                // Normal subtraction
                time1.set(1000,1000);
                time2.set(4000,2000);
                Fw::Time time3 = Fw::Time::sub(time2,time1);
                ASSERT_EQ(time3.m_timeBase,TB_NONE);
                ASSERT_EQ(time3.m_timeContext,0);
                ASSERT_EQ(time3.m_seconds,3000);
                ASSERT_EQ(time3.m_useconds,1000);

                // Rollover subtraction
                time1.set(1,999999);
                time2.set(2,000001);
                time3 = Fw::Time::sub(time2,time1);
                ASSERT_EQ(time3.m_timeBase,TB_NONE);
                ASSERT_EQ(time3.m_timeContext,0);
                EXPECT_EQ(time3.m_seconds,0);
                EXPECT_EQ(time3.m_useconds,2);
            }

            void test_InstantiateTest()
            {
                Fw::Time time(TB_NONE,1,2);
                ASSERT_EQ(time.m_timeBase,TB_NONE);
                ASSERT_EQ(time.m_timeContext,0);
                ASSERT_EQ(time.m_seconds,1);
                ASSERT_EQ(time.m_useconds,2);
                std::cout << time << std::endl;
            }

            void test_CopyTest()
            {
                Fw::Time time0;

                // make time that's guaranteed to be different from default
                Fw::Time time1(
                    (time0.getTimeBase() != TB_NONE ? TB_NONE : TB_PROC_TIME),
                    static_cast<FwTimeContextStoreType>(time0.getContext()+1),
                    time0.getSeconds()+1,
                    time0.getUSeconds()+1
                );

                // copy construction
                Fw::Time time2 = time1;
                ASSERT_EQ(time1.getSeconds(), time2.getSeconds());
                ASSERT_EQ(time1.getUSeconds(), time2.getUSeconds());
                ASSERT_EQ(time1.getTimeBase(), time2.getTimeBase());
                ASSERT_EQ(time1.getContext(), time2.getContext());

                // assignment operator
                Fw::Time time3;
                time3 = time1;
                ASSERT_EQ(time1.getSeconds(), time3.getSeconds());
                ASSERT_EQ(time1.getUSeconds(), time3.getUSeconds());
                ASSERT_EQ(time1.getTimeBase(), time3.getTimeBase());
                ASSERT_EQ(time1.getContext(), time3.getContext());

                // set method
                Fw::Time time4;
                time4.set(time1.getTimeBase(), time1.getContext(), time1.getSeconds(), time1.getUSeconds());
                ASSERT_EQ(time1.getSeconds(), time3.getSeconds());
                ASSERT_EQ(time1.getUSeconds(), time3.getUSeconds());
                ASSERT_EQ(time1.getTimeBase(), time3.getTimeBase());
                ASSERT_EQ(time1.getContext(), time3.getContext());

            }

            void test_ZeroTimeEquality()
            {
                Fw::Time time(TB_PROC_TIME,1,2);
                ASSERT_NE(time, Fw::ZERO_TIME);
                Fw::Time time2;
                ASSERT_EQ(time2, Fw::ZERO_TIME);
            }

            void test_TimeIntervalInstantiateTest()
            {
                Fw::TimeInterval time(1,2);
                ASSERT_EQ(time.getseconds(), 1);
                ASSERT_EQ(time.getuseconds(), 2);
                std::cout << time << std::endl;

                Fw::TimeInterval time2(time);
                ASSERT_EQ(time.getseconds(), 1);
                ASSERT_EQ(time.getuseconds(), 2);
                std::cout << time2 << std::endl;

            }

            void test_TimeIntervalComparisonTest()
            {
                Fw::TimeInterval t1(1, 0);
                Fw::TimeInterval t2(1, 0);
                Fw::TimeInterval t3(2, 0);
                Fw::TimeInterval t4(1, 500000);
                
                // Equality operators
                ASSERT_TRUE(t1 == t2);
                ASSERT_FALSE(t1 == t3);
                ASSERT_FALSE(t1 == t4);
                
                // Inequality operators
                ASSERT_FALSE(t1 != t2);
                ASSERT_TRUE(t1 != t3);
                ASSERT_TRUE(t1 != t4);
                
                // Greater than operators
                ASSERT_TRUE(t3 > t1);
                ASSERT_FALSE(t1 > t3);
                ASSERT_TRUE(t4 > t1);
                
                // Less than operators
                ASSERT_TRUE(t1 < t3);
                ASSERT_FALSE(t3 < t1);
                ASSERT_TRUE(t1 < t4);
                
                // Greater than or equal operators
                ASSERT_TRUE(t1 >= t2);
                ASSERT_TRUE(t3 >= t1);
                ASSERT_FALSE(t1 >= t3);
                
                // Less than or equal operators
                ASSERT_TRUE(t1 <= t2);
                ASSERT_TRUE(t1 <= t3);
                ASSERT_FALSE(t3 <= t1);
            }
            
            void test_TimeIntervalAdditionTest()
            {
                Fw::TimeInterval t1(1, 500000);
                Fw::TimeInterval t2(2, 600000);
                
                // Test instance add method
                t1.add(3, 700000);
                // 1 + 3 = 4s, 500000us + 700000us = 1s + 200000us -> 5s, 200000us
                ASSERT_EQ(t1.getseconds(), 5); 
                ASSERT_EQ(t1.getuseconds(), 200000);
                
                // Test static add method
                Fw::TimeInterval result = Fw::TimeInterval::add(t1, t2);
                // 5 + 2 = 7s, 200000us + 600000us = 1s + 800000us -> 7s, 800000us
                ASSERT_EQ(result.getseconds(), 7);
                ASSERT_EQ(result.getuseconds(), 800000);
            }
            
            void test_TimeIntervalCompareStaticTest()
            {
                Fw::TimeInterval t1(1, 0);
                Fw::TimeInterval t2(1, 0);
                Fw::TimeInterval t3(2, 0);
                Fw::TimeInterval t4(1, 500000);
                
                // Test static compare method
                ASSERT_EQ(Fw::TimeInterval::compare(t1, t2), Fw::TimeInterval::EQ);
                ASSERT_EQ(Fw::TimeInterval::compare(t1, t3), Fw::TimeInterval::LT);
                ASSERT_EQ(Fw::TimeInterval::compare(t3, t1), Fw::TimeInterval::GT);
                ASSERT_EQ(Fw::TimeInterval::compare(t1, t4), Fw::TimeInterval::LT);
                ASSERT_EQ(Fw::TimeInterval::compare(t4, t1), Fw::TimeInterval::GT);
            }

        };
}


TEST(TimeTestNominal,InstantiateTest) {
    Fw::TimeTester tester;
    tester.test_InstantiateTest();
}

TEST(TimeTestNominal,MathTest) {
    Fw::TimeTester tester;
    tester.test_MathTest();

}

TEST(TimeTestNominal,CopyTest) {
    Fw::TimeTester tester;
    tester.test_CopyTest();
}

TEST(TimeTestNominal,ZeroTimeEquality) {
    Fw::TimeTester tester;
    tester.test_ZeroTimeEquality();
}

TEST(TimeIntervalTestNominal,test_TimeIntervalInstantiateTest) {
    Fw::TimeTester tester;
    tester.test_TimeIntervalInstantiateTest();
}

TEST(TimeIntervalTestNominal,test_TimeIntervalComparisonTest) {
    Fw::TimeTester tester;
    tester.test_TimeIntervalComparisonTest();
}

TEST(TimeIntervalTestNominal,test_TimeIntervalAdditionTest) {
    Fw::TimeTester tester;
    tester.test_TimeIntervalAdditionTest();
}

TEST(TimeIntervalTestNominal,test_TimeIntervalCompareStaticTest) {
    Fw::TimeTester tester;
    tester.test_TimeIntervalCompareStaticTest();
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
