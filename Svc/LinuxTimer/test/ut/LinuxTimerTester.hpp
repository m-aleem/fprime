// ======================================================================
// \title  LinuxTimer/test/ut/Tester.hpp
// \author tim
// \brief  hpp file for LinuxTimer test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "LinuxTimerGTestBase.hpp"
#include "Svc/LinuxTimer/LinuxTimer.hpp"

namespace Svc {

  class LinuxTimerTester :
    public LinuxTimerGTestBase
  {

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:

      //! Construct object LinuxTimerTester
      //!
      LinuxTimerTester();

      //! Destroy object LinuxTimerTester
      //!
      ~LinuxTimerTester();

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------

      //! To do
      //!
      void runCycles();

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_CycleOut
      //!
      void from_CycleOut_handler(
          const FwIndexType portNum, /*!< The port number*/
          Os::RawTime &cycleStart /*!< Cycle start timer value*/
      );

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------

      //! Connect ports
      //!
      void connectPorts();

      //! Initialize components
      //!
      void initComponents();

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      LinuxTimer component;

      U32 m_numCalls;

  };

} // end namespace Svc

#endif
