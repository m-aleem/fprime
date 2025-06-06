// ======================================================================
// \title  Hash.hpp
// \author dinkel
// \brief  hpp file for Hash class
//
// \copyright
// Copyright 2009-2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef UTILS_HASH_BUFFER_HPP
#define UTILS_HASH_BUFFER_HPP

#include <Fw/FPrimeBasicTypes.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Types/Serializable.hpp>
#include <Utils/Hash/HashConfig.hpp>

namespace Utils {

//! \class HashBuffer
//! \brief A container class for holding a hash buffer
//!
class HashBuffer : public Fw::SerializeBufferBase {
  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct a HashBuffer object
    //!
    HashBuffer(const U8* args, FwSizeType size);
    HashBuffer(const HashBuffer& other);
    HashBuffer();

    //! Destroy a HashBuffer object
    //!
    virtual ~HashBuffer();

    // ----------------------------------------------------------------------
    // Public instance methods
    // ----------------------------------------------------------------------

    //! Assign a hash buffer from another hash buffer
    //!
    HashBuffer& operator=(const HashBuffer& other);

    //! Compare two hash buffers for equality
    //!
    bool operator==(const HashBuffer& other) const;

    //! Compare two hash buffers for inequality
    //!
    bool operator!=(const HashBuffer& other) const;

    //! Get the total buffer length of a hash buffer
    //!
    FwSizeType getBuffCapacity() const;  // !< returns capacity, not current size, of buffer

    //! Get a pointer to the buffer within the hash buffer
    //!
    U8* getBuffAddr();
    const U8* getBuffAddr() const;

    //! Convert bytes 0 through 3 of the hash data to a big-Endian U32 value
    U32 asBigEndianU32() const;

  private:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! The buffer which stores the hash digest
    //!
    U8 m_bufferData[HASH_DIGEST_LENGTH] = {};  // packet data buffer
};
}  // namespace Utils

#endif
