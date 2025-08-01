#include <Fw/Time/TimeInterval.hpp>
#include <Fw/FPrimeBasicTypes.hpp>

namespace Fw {
    TimeInterval::TimeInterval(const TimeInterval& other) : Serializable() {
        this->m_val = other.m_val;
    }

    TimeInterval::TimeInterval(U32 seconds, U32 useconds) : Serializable() {
        this->set(seconds,useconds);
    }

    void TimeInterval::set(U32 seconds, U32 useconds) {
        this->m_val.set(seconds, useconds);
    }

    TimeInterval& TimeInterval::operator=(const TimeInterval& other) {
        if (this != &other) {
            this->m_val = other.m_val;
        }
        return *this;
    }

    bool TimeInterval::operator==(const TimeInterval& other) const {
        return (TimeInterval::compare(*this, other) == EQ);
    }

    bool TimeInterval::operator!=(const TimeInterval& other) const {
        return (TimeInterval::compare(*this, other) != EQ);
    }

    bool TimeInterval::operator>(const TimeInterval& other) const {
        return (TimeInterval::compare(*this, other) == GT);
    }

    bool TimeInterval::operator<(const TimeInterval& other) const {
        return (TimeInterval::compare(*this, other) == LT);
    }

    bool TimeInterval::operator>=(const TimeInterval& other) const {
        TimeInterval::Comparison c = TimeInterval::compare(*this, other);
        return ((GT == c) or (EQ == c));
    }

    bool TimeInterval::operator<=(const TimeInterval& other) const {
        TimeInterval::Comparison c = TimeInterval::compare(*this, other);
        return ((LT == c) or (EQ == c));
    }

    SerializeStatus TimeInterval::serialize(SerializeBufferBase& buffer) const {
        // Deprecated method - calls new interface for backward compatibility
        return this->serializeTo(buffer);
    }

    SerializeStatus TimeInterval::deserialize(SerializeBufferBase& buffer) {
        // Deprecated method - calls new interface for backward compatibility
        return this->deserializeFrom(buffer);
    }

    SerializeStatus TimeInterval::serializeTo(SerializeBufferBase& buffer) const {
        // Use TimeIntervalValue's built-in serialization
        return this->m_val.serializeTo(buffer);
    }

    SerializeStatus TimeInterval::deserializeFrom(SerializeBufferBase& buffer) {
        // Use TimeIntervalValue's built-in deserialization
        return this->m_val.deserializeFrom(buffer);
    }

    U32 TimeInterval::getSeconds() const {
        return this->m_val.get_seconds();
    }

    U32 TimeInterval::getUSeconds() const {
        return this->m_val.get_useconds();
    }

    TimeInterval::Comparison TimeInterval ::
      compare(
          const TimeInterval &time1,
          const TimeInterval &time2
      )
    {
      const U32 s1 = time1.getSeconds();
      const U32 s2 = time2.getSeconds();
      const U32 us1 = time1.getUSeconds();
      const U32 us2 = time2.getUSeconds();

      if (s1 < s2) {
        return LT;
      } else if (s1 > s2) {
        return GT;
      } else if (us1 < us2) {
        return LT;
      } else if (us1 > us2) {
        return GT;
      } else {
        return EQ;
      }
    }

    TimeInterval TimeInterval ::
      add(
        const TimeInterval& a,
        const TimeInterval& b
      )
    {
      U32 seconds = a.getSeconds() + b.getSeconds();
      U32 uSeconds = a.getUSeconds() + b.getUSeconds();
      FW_ASSERT(uSeconds < 1999999);
      if (uSeconds >= 1000000) {
        ++seconds;
        uSeconds -= 1000000;
      }
      TimeInterval c(seconds,uSeconds);
      return c;
    }

    TimeInterval TimeInterval ::
      sub(
        const TimeInterval& t1, //!< TimeInterval t1
        const TimeInterval& t2 //!< TimeInterval t2
    )
    {
      const TimeInterval& minuend = (t1 > t2) ? t1 : t2;
      const TimeInterval& subtrahend = (t1 > t2) ? t2 : t1;

      U32 seconds = minuend.getSeconds() - subtrahend.getSeconds();
      U32 uSeconds;
      if (subtrahend.getUSeconds() > minuend.getUSeconds()) {
          seconds--;
          uSeconds = minuend.getUSeconds() + 1000000 - subtrahend.getUSeconds();
      } else {
          uSeconds = minuend.getUSeconds() - subtrahend.getUSeconds();
      }
      return TimeInterval(seconds, static_cast<U32>(uSeconds));
    }

    void TimeInterval::add(U32 seconds, U32 useconds) {
        U32 newSeconds = this->m_val.get_seconds() + seconds;
        U32 newUSeconds = this->m_val.get_useconds() + useconds;
        FW_ASSERT(newUSeconds < 1999999, static_cast<FwAssertArgType>(newUSeconds));
        if (newUSeconds >= 1000000) {
          newSeconds += 1;
          newUSeconds -= 1000000;
        }
        this->m_val.set(newSeconds, newUSeconds);
    }

#ifdef BUILD_UT
    std::ostream& operator<<(std::ostream& os, const TimeInterval& val) {

        os << "(" << val.getSeconds() << "s," << val.getUSeconds() << "us)";
        return os;
    }
#endif

}