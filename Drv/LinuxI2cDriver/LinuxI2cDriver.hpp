// ======================================================================
// \title  LinuxI2cDriver.hpp
// \author tcanham
// \brief  hpp file for LinuxI2cDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef LinuxI2cDriver_HPP
#define LinuxI2cDriver_HPP

#include "Drv/LinuxI2cDriver/LinuxI2cDriverComponentAc.hpp"

namespace Drv {

  class LinuxI2cDriver final :
    public LinuxI2cDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object LinuxI2cDriver
      //!
      LinuxI2cDriver(const char *const compName);

      bool open(const char* device);
      //! Destroy object LinuxI2cDriver
      //!
      ~LinuxI2cDriver();

    private:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for write
      //!
      I2cStatus write_handler(
          const FwIndexType portNum, /*!< The port number*/
          U32 addr,
          Fw::Buffer &serBuffer
      );

      //! Handler implementation for read
      //!
      I2cStatus read_handler(
          const FwIndexType portNum, /*!< The port number*/
          U32 addr,
          Fw::Buffer &serBuffer
      );

      //! Handler implementation for writeRead
      //!
      I2cStatus  writeRead_handler(
          const FwIndexType portNum, /*!< The port number*/
          U32 addr,
          Fw::Buffer &writeBuffer,
          Fw::Buffer &readBuffer
      );

      // Prevent unused field error when using stub
      #ifndef STUBBED_LINUX_I2C_DRIVER
      int m_fd; //!< i2c file descriptor
      #endif
    };

} // end namespace Drv

#endif
