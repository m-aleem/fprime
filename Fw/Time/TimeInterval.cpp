#include <Fw/Time/TimeInterval.hpp>
#include <Fw/FPrimeBasicTypes.hpp>

namespace Fw {

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

    TimeInterval::Comparison TimeInterval ::
      compare(
          const TimeInterval &time1,
          const TimeInterval &time2
      )
    {
      const U32 s1 = time1.getseconds();
      const U32 s2 = time2.getseconds();
      const U32 us1 = time1.getuseconds();
      const U32 us2 = time2.getuseconds();

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
      U32 seconds = a.getseconds() + b.getseconds();
      U32 uSeconds = a.getuseconds() + b.getuseconds();
      FW_ASSERT(uSeconds < 1999999);
      if (uSeconds >= 1000000) {
        ++seconds;
        uSeconds -= 1000000;
      }
      TimeInterval c(seconds, uSeconds);
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

      U32 seconds = minuend.getseconds() - subtrahend.getseconds();
      U32 uSeconds;
      if (subtrahend.getuseconds() > minuend.getuseconds()) {
          seconds--;
          uSeconds = minuend.getuseconds() + 1000000 - subtrahend.getuseconds();
      } else {
          uSeconds = minuend.getuseconds() - subtrahend.getuseconds();
      }
      return TimeInterval(seconds, static_cast<U32>(uSeconds));
    }

    void TimeInterval::add(U32 seconds, U32 useconds) {
        U32 new_seconds = this->getseconds() + seconds;
        U32 new_useconds = this->getuseconds() + useconds;
        
        FW_ASSERT(new_useconds < 1999999, static_cast<FwAssertArgType>(new_useconds));
        if (new_useconds >= 1000000) {
          new_seconds += 1;
          new_useconds -= 1000000;
        }
        
        this->set(new_seconds, new_useconds);
    }

#ifdef BUILD_UT
    std::ostream& operator<<(std::ostream& os, const TimeInterval& val) {
        os << "(" << val.getseconds() << "s," << val.getuseconds() << "us)";
        return os;
    }
#endif

}
