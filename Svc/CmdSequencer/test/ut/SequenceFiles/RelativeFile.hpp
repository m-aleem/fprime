// ====================================================================== 
// \title  RelativeFile.hpp
// \author Rob Bocchino
// \brief  RelativeFile interface
//
// \copyright
// Copyright (C) 2009-2018 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.

#ifndef Svc_SequenceFiles_RelativeFile_HPP
#define Svc_SequenceFiles_RelativeFile_HPP

#include "Svc/CmdSequencer/test/ut/SequenceFiles/File.hpp"
#include "Svc/CmdSequencer/CmdSequencerImpl.hpp"

namespace Svc {

  namespace SequenceFiles {

    //! A file containing n commands, each of which has a non-zero
    //! relative time.
    class RelativeFile :
      public File
    {

      public:

        //! Construct a RelativeFile
        RelativeFile(
            const U32 a_n, //!< The number of records
            const Format::t a_format //!< The file format
        );

      public:

        //! Serialize the file in F Prime format
        void serializeFPrime(
            Fw::SerializeBufferBase& buffer //!< The buffer
        );

        //! Serialize the file in AMPCS format
        void serializeAMPCS(
            Fw::SerializeBufferBase& buffer //!< The buffer
        );

      public:

        //! The number of records
        const U32 n;

    };

  }

}

#endif
