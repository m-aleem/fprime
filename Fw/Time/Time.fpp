module Fw {
  
  type Time

  @ Time port
  port Time(
    ref $time: Fw.Time @< Reference to Time object
  )

  @ Data structure for Time Interval
  struct TimeIntervalType {
    seconds: U32  # seconds portion of TimeInterval
    useconds: U32  # microseconds portion of TimeInterval
  }

  @ Time interval port
  port TimeInterval(
    ref timeInterval: Fw.TimeIntervalType @< Reference to TimeInterval object
  )

}
