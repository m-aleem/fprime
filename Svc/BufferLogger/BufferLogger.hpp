// ======================================================================
// \title  BufferLogger.hpp
// \author bocchino, dinkel, mereweth
// \brief  Svc Buffer Logger interface
//
// \copyright
// Copyright (C) 2015-2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef Svc_BufferLogger_HPP
#define Svc_BufferLogger_HPP

#include "Svc/BufferLogger/BufferLoggerComponentAc.hpp"
#include "Os/File.hpp"
#include "Fw/Types/String.hpp"
#include "Fw/Types/Assert.hpp"
#include "Os/Mutex.hpp"
#include "Utils/Hash/Hash.hpp"

namespace Svc {

// Forward declaration for UTs
  namespace Logging {
    class CloseFileTester;
    class SendBuffersTester;
    class OnOffTester;
  }
  namespace Errors {
    class BufferLoggerTester;
  }


  class BufferLogger final :
    public BufferLoggerComponentBase
  {

    friend class BufferLoggerTester;
    friend class Svc::Logging::CloseFileTester;
    friend class Svc::Logging::SendBuffersTester;
    friend class Svc::Logging::OnOffTester;
    friend class Svc::Errors::BufferLoggerTester;

    private:

      // ----------------------------------------------------------------------
      // Types
      // ----------------------------------------------------------------------

      //! A BufferLogger file
      class File {

        friend class BufferLoggerTester;
        friend class Svc::Logging::CloseFileTester;
        friend class Svc::Logging::SendBuffersTester;
        friend class Svc::Logging::OnOffTester;
        friend class Svc::Errors::BufferLoggerTester;

        public:

          //! The file mode
          struct Mode {
            typedef enum {
              CLOSED = 0,
              OPEN = 1
            } t;
          };

        public:

          //! Construct a File object
          File(
              BufferLogger& bufferLogger //!< The enclosing BufferLogger instance
          );

          //! Destroy a File object
          ~File();

        public:

          //! Set File object parameters
          void init(
              const char *const prefix, //!< The file name prefix
              const char *const suffix, //!< The file name suffix
              const FwSizeType maxSize, //!< The maximum file size
              const U8 sizeOfSize //!< The number of bytes to use when storing the size field and the start of each buffer)
          );

          //! Set base file name
          void setBaseName(
              const Fw::StringBase& baseName //!< The base file name; used with prefix, unique counter value, and suffix
          );

          //! Log a buffer
          void logBuffer(
              const U8 *const data, //!< The buffer data
              const FwSizeType size //!< The size
          );

          //! Close the file and emit an event
          void closeAndEmitEvent();

          //! Flush the file
          bool flush();

        private:

          //! Open the file
          void open();

          //! Write a buffer to a file
          //! \return Success or failure
          bool writeBuffer(
              const U8 *const data, //!< The buffer data
              const FwSizeType size //!< The number of bytes to write
          );

          //! Write the size field of a buffer
          //! \return Success or failure
          bool writeSize(
              const FwSizeType size //!< The size
          );

          //! Write bytes to a file
          //! \return Success or failure
          bool writeBytes(
              const void *const data, //!< The data
              const FwSizeType length //!< The number of bytes to write
          );

          //! Write a hash file
          void writeHashFile();

          //! Close the file
          void close();

        private:

          //! The enclosing BufferLogger instance
          BufferLogger& m_bufferLogger;

          //! The prefix to use for file names
          Fw::String m_prefix;

          //! The suffix to use for file names
          Fw::String m_suffix;

          //! The file name base
          Fw::String m_baseName;

          //! The counter to use for the same file name
          FwSizeType m_fileCounter;

          //! The maximum file size
          FwSizeType m_maxSize;

          //! The number of bytes to use when storing the size field at the start of each buffer
          U8 m_sizeOfSize;

          //! The name of the currently open file
          Fw::String m_name;

          // The current mode
          Mode::t m_mode;

          //! The underlying Os::File representation
          Os::File m_osFile;

          //! The number of bytes written to the current file
          FwSizeType m_bytesWritten;

      }; // class File

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Create a BufferLogger object
      BufferLogger(
          const char *const compName /*!< The component name*/
      );


      // ----------------------------------------------------------------------
      // Public methods
      // ----------------------------------------------------------------------

      //! Set up log file parameters
      void initLog(
          const char *const logFilePrefix, //!< The log file name prefix
          const char *const logFileSuffix, //!< The log file name suffix
          const FwSizeType maxFileSize, //!< The maximum file size
          const U8 sizeOfSize //!< The number of bytes to use when storing the size field at the start of each buffer
      );

    private:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for bufferSendIn
      //!
      void bufferSendIn_handler(
          const FwIndexType portNum, //!< The port number
          Fw::Buffer& fwBuffer
      );

      //! Handler implementation for comIn
      //!
      void comIn_handler(
          const FwIndexType portNum, //!< The port number
          Fw::ComBuffer &data, //!< Buffer containing packet data
          U32 context //!< Call context value; meaning chosen by user
      );

      //! Handler implementation for pingIn
      //!
      void pingIn_handler(
          const FwIndexType portNum, //!< The port number
          U32 key //!< Value to return to pinger
      );

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const FwIndexType portNum, /*!< The port number*/
          U32 context /*!< The call order*/
      );

    private:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for BL_OpenFile command handler
      //! Open a new log file with specified name; required before activating logging
      void BL_OpenFile_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CmdStringArg& file
      );

      //! Implementation for BL_CloseFile command handler
      //! Close the currently open log file, if any
      void BL_CloseFile_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for BL_SetLogging command handler
      //! Sets the volatile logging state
      void BL_SetLogging_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          BufferLogger_LogState state
      );

      //! Implementation for BL_FlushFile command handler
      //! Flushes the current open log file to disk
      void BL_FlushFile_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

  private:

      // ----------------------------------------------------------------------
      // Private instance variables
      // ----------------------------------------------------------------------

      //! The logging state
      BufferLogger_LogState m_state;

      //! The file
      File m_file;

  };

}

#endif
