#ifndef FW_TIME_INTERVAL_HPP
#define FW_TIME_INTERVAL_HPP

#include <Fw/FPrimeBasicTypes.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Time/TimeIntervalTypeSerializableAc.hpp>

//!
//! @class TimeInterval
//! @brief A class to represent a time interval holding two U32 seconds and microseconds values.
//!
//! The TimeInterval class is designed to hold a time interval and provides various methods
//! to manipulate and compare time intervals. It derives from the auto-generated TimeIntervalType
//! which supports serialization and extends it with additional functionality.
//!

namespace Fw {

    // Extend the auto-generated class with additional functionality
    class TimeInterval : public TimeIntervalType {
        public:
            // Inherit all constructors from TimeIntervalType
            using TimeIntervalType::TimeIntervalType;

            // For backward compatibility
            U32 getSeconds() const { return this->getseconds(); }
            U32 getUSeconds() const { return this->getuseconds(); }

            // Additional operators not provided by auto-generated code
            bool operator>(const TimeInterval& other) const;
            bool operator<(const TimeInterval& other) const;
            bool operator>=(const TimeInterval& other) const;
            bool operator<=(const TimeInterval& other) const;

            // Addd seconds and microseconds to existing time interval
            void add(U32 seconds, U32 mseconds); 

            //! The type of a comparison result
            typedef enum {
              LT = -1,
              EQ = 0,
              GT = 1,
              INCOMPARABLE = 2
            } Comparison;

            //! Compare two time intervals
            //! A time interval is considered greater than another if it spans a longer duration
            //! The comparison is done on the seconds first, then the microseconds if the seconds are equal
            //! \return TimeInterval result
            static Comparison compare(
                const TimeInterval &time1, //!< TimeInterval 1
                const TimeInterval &time2 //!< TimeInterval 2
            );

            //! Add two time intervals
            //! Adds the seconds and microseconds fields of two time intervals together
            //! \return TimeInterval result
            static TimeInterval add(
                const TimeInterval& a, //!< TimeInterval a
                const TimeInterval& b //!< TimeInterval b
            );

            //! Subtract two time intervals
            //! This computes the absolute value of the difference between two time intervals
            //! For example if t1=(0s, 5us) and t2=(0s, 3us), the result is (0s, 2us).
            //! This operation is commutative, i.e. the result is the same regardless of the order of the arguments.
            //! \return TimeInterval result
            static TimeInterval sub(
                const TimeInterval& t1, //!< TimeInterval 1
                const TimeInterval& t2 //!< TimeInterval 2
            );

    };

}

#endif
