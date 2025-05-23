// ======================================================================
// \title  LinuxI2cDriver.cpp
// \author tcanham
// \brief  cpp file for LinuxI2cDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include "Fw/Types/Assert.hpp"
#include <Fw/FPrimeBasicTypes.hpp>
#include <Drv/LinuxI2cDriver/LinuxI2cDriver.hpp>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

LinuxI2cDriver ::LinuxI2cDriver(
        const char *const compName
    ) : LinuxI2cDriverComponentBase(compName)
  {

  }

  LinuxI2cDriver ::
    ~LinuxI2cDriver()
  {

  }

  bool LinuxI2cDriver::open(const char* device) {
    return true;
  }


  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  // Note this port handler is guarded, so we can make the ioctl call

  I2cStatus LinuxI2cDriver ::
    write_handler(
        const FwIndexType portNum,
        U32 addr,
        Fw::Buffer &serBuffer
    )
  {
    return I2cStatus::I2C_OK;
  }

  Drv::I2cStatus LinuxI2cDriver ::
    read_handler(
        const FwIndexType portNum,
        U32 addr,
        Fw::Buffer &serBuffer
    )
  {
    return I2cStatus::I2C_OK;
  }

  Drv::I2cStatus LinuxI2cDriver ::
    writeRead_handler(
      const FwIndexType portNum, /*!< The port number*/
      U32 addr,
      Fw::Buffer &writeBuffer,
      Fw::Buffer &readBuffer
  ){
    return I2cStatus::I2C_OK;
  }

} // end namespace Drv
