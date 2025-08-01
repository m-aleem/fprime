#include <Fw/FPrimeBasicTypes.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Types/Serializable.hpp>
#include <Fw/Types/StringType.hpp>
#include <cstdio>
#include <cstring>  // memcpy
#ifdef BUILD_UT
#include <Fw/Types/String.hpp>
#include <iomanip>
#endif

// Some macros/functions to optimize for architectures

namespace Fw {

Serializable::Serializable() {}

Serializable::~Serializable() {}

// ----------------------------------------------------------------------
// Default implementations for new serialization methods
//
// These are provided for backward compatibility specifically for autocoding that
// does not yet support the new serialization methods.
// ----------------------------------------------------------------------

SerializeStatus Serializable::serializeTo(SerializeBufferBase& buffer) const {
    // Default implementation for base class - derived classes should override this method
    return FW_SERIALIZE_FORMAT_ERROR;
}

SerializeStatus Serializable::deserializeFrom(SerializeBufferBase& buffer) {
    // Default implementation for base class - derived classes should override this method
    return FW_DESERIALIZE_FORMAT_ERROR;
}

// ----------------------------------------------------------------------
#if FW_SERIALIZABLE_TO_STRING || FW_ENABLE_TEXT_LOGGING || BUILD_UT

void Serializable::toString(StringBase& text) const {
    text = "NOSPEC";  // set to not specified.
}

#endif

#ifdef BUILD_UT
std::ostream& operator<<(std::ostream& os, const Serializable& val) {
    Fw::String out;
    val.toString(out);

    os << out;

    return os;
}
#endif

SerializeBufferBase::SerializeBufferBase() : m_serLoc(0), m_deserLoc(0) {}

SerializeBufferBase::~SerializeBufferBase() {}

void SerializeBufferBase::copyFrom(const SerializeBufferBase& src) {
    this->m_serLoc = src.m_serLoc;
    this->m_deserLoc = src.m_deserLoc;
    FW_ASSERT(src.getBuffAddr());
    FW_ASSERT(this->getBuffAddr());
    // destination has to be same or bigger
    FW_ASSERT(src.getBuffLength() <= this->getBuffCapacity(), static_cast<FwAssertArgType>(src.getBuffLength()),
              static_cast<FwAssertArgType>(this->getBuffLength()));
    (void)memcpy(this->getBuffAddr(), src.getBuffAddr(), static_cast<size_t>(this->m_serLoc));
}

// Copy constructor doesn't make sense in this virtual class as there is nothing to copy. Derived classes should
// call the empty constructor and then call their own copy function
SerializeBufferBase& SerializeBufferBase::operator=(const SerializeBufferBase& src) {  // lgtm[cpp/rule-of-two]
    this->copyFrom(src);
    return *this;
}

// serialization routines

SerializeStatus SerializeBufferBase::serializeFrom(U8 val) {
    if (this->m_serLoc + static_cast<Serializable::SizeType>(sizeof(val)) - 1 >= this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }
    FW_ASSERT(this->getBuffAddr());
    this->getBuffAddr()[this->m_serLoc] = val;
    this->m_serLoc += static_cast<Serializable::SizeType>(sizeof(val));
    this->m_deserLoc = 0;

    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::serializeFrom(I8 val) {
    if (this->m_serLoc + static_cast<Serializable::SizeType>(sizeof(val)) - 1 >= this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }
    FW_ASSERT(this->getBuffAddr());
    this->getBuffAddr()[this->m_serLoc + 0] = static_cast<U8>(val);
    this->m_serLoc += static_cast<Serializable::SizeType>(sizeof(val));
    this->m_deserLoc = 0;
    return FW_SERIALIZE_OK;
}

#if FW_HAS_16_BIT == 1
SerializeStatus SerializeBufferBase::serializeFrom(U16 val) {
    if (this->m_serLoc + static_cast<Serializable::SizeType>(sizeof(val)) - 1 >= this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    this->getBuffAddr()[this->m_serLoc + 0] = static_cast<U8>(val >> 8);
    this->getBuffAddr()[this->m_serLoc + 1] = static_cast<U8>(val);
    this->m_serLoc += static_cast<Serializable::SizeType>(sizeof(val));
    this->m_deserLoc = 0;
    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::serializeFrom(I16 val) {
    if (this->m_serLoc + static_cast<Serializable::SizeType>(sizeof(val)) - 1 >= this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    this->getBuffAddr()[this->m_serLoc + 0] = static_cast<U8>(val >> 8);
    this->getBuffAddr()[this->m_serLoc + 1] = static_cast<U8>(val);
    this->m_serLoc += static_cast<Serializable::SizeType>(sizeof(val));
    this->m_deserLoc = 0;
    return FW_SERIALIZE_OK;
}
#endif
#if FW_HAS_32_BIT == 1
SerializeStatus SerializeBufferBase::serializeFrom(U32 val) {
    if (this->m_serLoc + static_cast<Serializable::SizeType>(sizeof(val)) - 1 >= this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    this->getBuffAddr()[this->m_serLoc + 0] = static_cast<U8>(val >> 24);
    this->getBuffAddr()[this->m_serLoc + 1] = static_cast<U8>(val >> 16);
    this->getBuffAddr()[this->m_serLoc + 2] = static_cast<U8>(val >> 8);
    this->getBuffAddr()[this->m_serLoc + 3] = static_cast<U8>(val);
    this->m_serLoc += static_cast<Serializable::SizeType>(sizeof(val));
    this->m_deserLoc = 0;
    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::serializeFrom(I32 val) {
    if (this->m_serLoc + static_cast<Serializable::SizeType>(sizeof(val)) - 1 >= this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    this->getBuffAddr()[this->m_serLoc + 0] = static_cast<U8>(val >> 24);
    this->getBuffAddr()[this->m_serLoc + 1] = static_cast<U8>(val >> 16);
    this->getBuffAddr()[this->m_serLoc + 2] = static_cast<U8>(val >> 8);
    this->getBuffAddr()[this->m_serLoc + 3] = static_cast<U8>(val);
    this->m_serLoc += static_cast<Serializable::SizeType>(sizeof(val));
    this->m_deserLoc = 0;
    return FW_SERIALIZE_OK;
}
#endif

#if FW_HAS_64_BIT == 1
SerializeStatus SerializeBufferBase::serializeFrom(U64 val) {
    if (this->m_serLoc + static_cast<Serializable::SizeType>(sizeof(val)) - 1 >= this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    this->getBuffAddr()[this->m_serLoc + 0] = static_cast<U8>(val >> 56);
    this->getBuffAddr()[this->m_serLoc + 1] = static_cast<U8>(val >> 48);
    this->getBuffAddr()[this->m_serLoc + 2] = static_cast<U8>(val >> 40);
    this->getBuffAddr()[this->m_serLoc + 3] = static_cast<U8>(val >> 32);
    this->getBuffAddr()[this->m_serLoc + 4] = static_cast<U8>(val >> 24);
    this->getBuffAddr()[this->m_serLoc + 5] = static_cast<U8>(val >> 16);
    this->getBuffAddr()[this->m_serLoc + 6] = static_cast<U8>(val >> 8);
    this->getBuffAddr()[this->m_serLoc + 7] = static_cast<U8>(val);
    this->m_serLoc += static_cast<Serializable::SizeType>(sizeof(val));
    this->m_deserLoc = 0;
    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::serializeFrom(I64 val) {
    if (this->m_serLoc + static_cast<Serializable::SizeType>(sizeof(val)) - 1 >= this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    this->getBuffAddr()[this->m_serLoc + 0] = static_cast<U8>(val >> 56);
    this->getBuffAddr()[this->m_serLoc + 1] = static_cast<U8>(val >> 48);
    this->getBuffAddr()[this->m_serLoc + 2] = static_cast<U8>(val >> 40);
    this->getBuffAddr()[this->m_serLoc + 3] = static_cast<U8>(val >> 32);
    this->getBuffAddr()[this->m_serLoc + 4] = static_cast<U8>(val >> 24);
    this->getBuffAddr()[this->m_serLoc + 5] = static_cast<U8>(val >> 16);
    this->getBuffAddr()[this->m_serLoc + 6] = static_cast<U8>(val >> 8);
    this->getBuffAddr()[this->m_serLoc + 7] = static_cast<U8>(val);
    this->m_serLoc += static_cast<Serializable::SizeType>(sizeof(val));
    this->m_deserLoc = 0;
    return FW_SERIALIZE_OK;
}
#endif

SerializeStatus SerializeBufferBase::serializeFrom(F64 val) {
    // floating point values need to be byte-swapped as well, so copy to U64 and use that routine
    U64 u64Val;
    (void)memcpy(&u64Val, &val, sizeof(val));
    return this->serializeFrom(u64Val);
}

SerializeStatus SerializeBufferBase::serializeFrom(F32 val) {
    // floating point values need to be byte-swapped as well, so copy to U32 and use that routine
    U32 u32Val;
    (void)memcpy(&u32Val, &val, sizeof(val));
    return this->serializeFrom(u32Val);
}

SerializeStatus SerializeBufferBase::serializeFrom(bool val) {
    if (this->m_serLoc + static_cast<Serializable::SizeType>(sizeof(U8)) - 1 >= this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }

    FW_ASSERT(this->getBuffAddr());
    if (val) {
        this->getBuffAddr()[this->m_serLoc + 0] = FW_SERIALIZE_TRUE_VALUE;
    } else {
        this->getBuffAddr()[this->m_serLoc + 0] = FW_SERIALIZE_FALSE_VALUE;
    }

    this->m_serLoc += static_cast<Serializable::SizeType>(sizeof(U8));
    this->m_deserLoc = 0;
    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::serializeFrom(const void* val) {
    if (this->m_serLoc + static_cast<Serializable::SizeType>(sizeof(void*)) - 1 >= this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }

    return this->serializeFrom(reinterpret_cast<PlatformPointerCastType>(val));
}

SerializeStatus SerializeBufferBase::serializeFrom(const U8* buff, Serializable::SizeType length) {
    return this->serializeFrom(buff, static_cast<FwSizeType>(length), Serialization::INCLUDE_LENGTH);
}

SerializeStatus SerializeBufferBase::serializeFrom(const U8* buff, FwSizeType length, Fw::Serialization::t mode) {
    // First serialize length
    SerializeStatus stat;
    if (mode == Serialization::INCLUDE_LENGTH) {
        stat = this->serializeFrom(static_cast<FwSizeStoreType>(length));
        if (stat != FW_SERIALIZE_OK) {
            return stat;
        }
    }

    // make sure we have enough space
    if (this->m_serLoc + length > this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }

    // copy buffer to our buffer
    (void)memcpy(&this->getBuffAddr()[this->m_serLoc], buff, static_cast<size_t>(length));
    this->m_serLoc += static_cast<Serializable::SizeType>(length);
    this->m_deserLoc = 0;

    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::serializeFrom(const Serializable& val) {
    // Smart fallback approach for backward compatibility:
    // Try new interface first, but if it returns FORMAT_ERROR (indicating default implementation),
    // fall back to old interface. This bridges auto-generated enums (old interface only) 
    // with new serialization infrastructure.
    SerializeStatus status = val.serializeTo(*this);
    if (status == FW_SERIALIZE_FORMAT_ERROR) {
        // Fallback to old interface for backward compatibility
        status = val.serialize(*this);
    }
    return status;
}

SerializeStatus SerializeBufferBase::serializeFrom(const SerializeBufferBase& val) {
    Serializable::SizeType size = val.getBuffLength();
    if (this->m_serLoc + size + static_cast<Serializable::SizeType>(sizeof(FwSizeStoreType)) >
        this->getBuffCapacity()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }

    // First, serialize size
    SerializeStatus stat = this->serializeFrom(static_cast<FwSizeStoreType>(size));
    if (stat != FW_SERIALIZE_OK) {
        return stat;
    }

    FW_ASSERT(this->getBuffAddr());
    FW_ASSERT(val.getBuffAddr());
    // serialize buffer
    (void)memcpy(&this->getBuffAddr()[this->m_serLoc], val.getBuffAddr(), static_cast<size_t>(size));
    this->m_serLoc += size;
    this->m_deserLoc = 0;

    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::serializeSize(const FwSizeType size) {
    SerializeStatus status = FW_SERIALIZE_OK;
    if ((size < std::numeric_limits<FwSizeStoreType>::min()) || (size > std::numeric_limits<FwSizeStoreType>::max())) {
        status = FW_SERIALIZE_FORMAT_ERROR;
    }
    if (status == FW_SERIALIZE_OK) {
        status = this->serializeFrom(static_cast<FwSizeStoreType>(size));
    }
    return status;
}

// deserialization routines

SerializeStatus SerializeBufferBase::deserializeTo(U8& val) {
    // check for room
    if (this->getBuffLength() == this->m_deserLoc) {
        return FW_DESERIALIZE_BUFFER_EMPTY;
    } else if (this->getBuffLength() - this->m_deserLoc < static_cast<Serializable::SizeType>(sizeof(val))) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }
    // read from current location
    FW_ASSERT(this->getBuffAddr());
    val = this->getBuffAddr()[this->m_deserLoc + 0];
    this->m_deserLoc += static_cast<Serializable::SizeType>(sizeof(val));
    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::deserializeTo(I8& val) {
    // check for room
    if (this->getBuffLength() == this->m_deserLoc) {
        return FW_DESERIALIZE_BUFFER_EMPTY;
    } else if (this->getBuffLength() - this->m_deserLoc < static_cast<Serializable::SizeType>(sizeof(val))) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }
    // read from current location
    FW_ASSERT(this->getBuffAddr());
    val = static_cast<I8>(this->getBuffAddr()[this->m_deserLoc + 0]);
    this->m_deserLoc += static_cast<Serializable::SizeType>(sizeof(val));
    return FW_SERIALIZE_OK;
}

#if FW_HAS_16_BIT == 1
SerializeStatus SerializeBufferBase::deserializeTo(U16& val) {
    // check for room
    if (this->getBuffLength() == this->m_deserLoc) {
        return FW_DESERIALIZE_BUFFER_EMPTY;
    } else if (this->getBuffLength() - this->m_deserLoc < static_cast<Serializable::SizeType>(sizeof(val))) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }
    // read from current location
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    val = static_cast<U16>(((this->getBuffAddr()[this->m_deserLoc + 1]) << 0) |
                           ((this->getBuffAddr()[this->m_deserLoc + 0]) << 8));
    this->m_deserLoc += static_cast<Serializable::SizeType>(sizeof(val));
    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::deserializeTo(I16& val) {
    // check for room
    if (this->getBuffLength() == this->m_deserLoc) {
        return FW_DESERIALIZE_BUFFER_EMPTY;
    } else if (this->getBuffLength() - this->m_deserLoc < static_cast<Serializable::SizeType>(sizeof(val))) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }
    // read from current location
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    val = static_cast<I16>(((this->getBuffAddr()[this->m_deserLoc + 1]) << 0) |
                           ((this->getBuffAddr()[this->m_deserLoc + 0]) << 8));
    this->m_deserLoc += static_cast<Serializable::SizeType>(sizeof(val));
    return FW_SERIALIZE_OK;
}
#endif
#if FW_HAS_32_BIT == 1
SerializeStatus SerializeBufferBase::deserializeTo(U32& val) {
    // check for room
    if (this->getBuffLength() == this->m_deserLoc) {
        return FW_DESERIALIZE_BUFFER_EMPTY;
    } else if (this->getBuffLength() - this->m_deserLoc < static_cast<Serializable::SizeType>(sizeof(val))) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }
    // read from current location
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    val = (static_cast<U32>(this->getBuffAddr()[this->m_deserLoc + 3]) << 0) |
          (static_cast<U32>(this->getBuffAddr()[this->m_deserLoc + 2]) << 8) |
          (static_cast<U32>(this->getBuffAddr()[this->m_deserLoc + 1]) << 16) |
          (static_cast<U32>(this->getBuffAddr()[this->m_deserLoc + 0]) << 24);
    this->m_deserLoc += static_cast<Serializable::SizeType>(sizeof(val));
    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::deserializeTo(I32& val) {
    // check for room
    if (this->getBuffLength() == this->m_deserLoc) {
        return FW_DESERIALIZE_BUFFER_EMPTY;
    } else if (this->getBuffLength() - this->m_deserLoc < static_cast<Serializable::SizeType>(sizeof(val))) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }
    // read from current location
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    val = (static_cast<I32>(this->getBuffAddr()[this->m_deserLoc + 3]) << 0) |
          (static_cast<I32>(this->getBuffAddr()[this->m_deserLoc + 2]) << 8) |
          (static_cast<I32>(this->getBuffAddr()[this->m_deserLoc + 1]) << 16) |
          (static_cast<I32>(this->getBuffAddr()[this->m_deserLoc + 0]) << 24);
    this->m_deserLoc += static_cast<Serializable::SizeType>(sizeof(val));
    return FW_SERIALIZE_OK;
}
#endif

#if FW_HAS_64_BIT == 1

SerializeStatus SerializeBufferBase::deserializeTo(U64& val) {
    // check for room
    if (this->getBuffLength() == this->m_deserLoc) {
        return FW_DESERIALIZE_BUFFER_EMPTY;
    } else if (this->getBuffLength() - this->m_deserLoc < static_cast<Serializable::SizeType>(sizeof(val))) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }
    // read from current location
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    val = (static_cast<U64>(this->getBuffAddr()[this->m_deserLoc + 7]) << 0) |
          (static_cast<U64>(this->getBuffAddr()[this->m_deserLoc + 6]) << 8) |
          (static_cast<U64>(this->getBuffAddr()[this->m_deserLoc + 5]) << 16) |
          (static_cast<U64>(this->getBuffAddr()[this->m_deserLoc + 4]) << 24) |
          (static_cast<U64>(this->getBuffAddr()[this->m_deserLoc + 3]) << 32) |
          (static_cast<U64>(this->getBuffAddr()[this->m_deserLoc + 2]) << 40) |
          (static_cast<U64>(this->getBuffAddr()[this->m_deserLoc + 1]) << 48) |
          (static_cast<U64>(this->getBuffAddr()[this->m_deserLoc + 0]) << 56);

    this->m_deserLoc += static_cast<Serializable::SizeType>(sizeof(val));
    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::deserializeTo(I64& val) {
    // check for room
    if (this->getBuffLength() == this->m_deserLoc) {
        return FW_DESERIALIZE_BUFFER_EMPTY;
    } else if (this->getBuffLength() - this->m_deserLoc < static_cast<Serializable::SizeType>(sizeof(val))) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }
    // read from current location
    FW_ASSERT(this->getBuffAddr());
    // MSB first
    val = (static_cast<I64>(this->getBuffAddr()[this->m_deserLoc + 7]) << 0) |
          (static_cast<I64>(this->getBuffAddr()[this->m_deserLoc + 6]) << 8) |
          (static_cast<I64>(this->getBuffAddr()[this->m_deserLoc + 5]) << 16) |
          (static_cast<I64>(this->getBuffAddr()[this->m_deserLoc + 4]) << 24) |
          (static_cast<I64>(this->getBuffAddr()[this->m_deserLoc + 3]) << 32) |
          (static_cast<I64>(this->getBuffAddr()[this->m_deserLoc + 2]) << 40) |
          (static_cast<I64>(this->getBuffAddr()[this->m_deserLoc + 1]) << 48) |
          (static_cast<I64>(this->getBuffAddr()[this->m_deserLoc + 0]) << 56);
    this->m_deserLoc += static_cast<Serializable::SizeType>(sizeof(val));
    return FW_SERIALIZE_OK;
}
#endif

SerializeStatus SerializeBufferBase::deserializeTo(F64& val) {
    // deserialize as 64-bit int to handle endianness
    U64 tempVal;
    SerializeStatus stat = this->deserializeTo(tempVal);
    if (stat != FW_SERIALIZE_OK) {
        return stat;
    }
    // copy to argument
    (void)memcpy(&val, &tempVal, sizeof(val));

    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::deserializeTo(bool& val) {
    // check for room
    if (this->getBuffLength() == this->m_deserLoc) {
        return FW_DESERIALIZE_BUFFER_EMPTY;
    } else if (this->getBuffLength() - this->m_deserLoc < static_cast<Serializable::SizeType>(sizeof(U8))) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }
    // read from current location
    FW_ASSERT(this->getBuffAddr());
    if (FW_SERIALIZE_TRUE_VALUE == this->getBuffAddr()[this->m_deserLoc + 0]) {
        val = true;
    } else if (FW_SERIALIZE_FALSE_VALUE == this->getBuffAddr()[this->m_deserLoc + 0]) {
        val = false;
    } else {
        return FW_DESERIALIZE_FORMAT_ERROR;
    }

    this->m_deserLoc += static_cast<Serializable::SizeType>(sizeof(U8));
    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::deserializeTo(void*& val) {
    // Deserialize as pointer cast, then convert to void*
    PlatformPointerCastType pointerCastVal = 0;
    const SerializeStatus stat = this->deserializeTo(pointerCastVal);
    if (stat == FW_SERIALIZE_OK) {
        val = reinterpret_cast<void*>(pointerCastVal);
    }
    return stat;
}

SerializeStatus SerializeBufferBase::deserializeTo(F32& val) {
    // deserialize as 64-bit int to handle endianness
    U32 tempVal;
    SerializeStatus stat = this->deserializeTo(tempVal);
    if (stat != FW_SERIALIZE_OK) {
        return stat;
    }
    (void)memcpy(&val, &tempVal, sizeof(val));

    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::deserializeTo(U8* buff, Serializable::SizeType& length) {
    FwSizeType length_in_out = static_cast<FwSizeType>(length);
    SerializeStatus status = this->deserializeTo(buff, length_in_out, Serialization::INCLUDE_LENGTH);
    length = static_cast<Serializable::SizeType>(length_in_out);
    return status;
}

SerializeStatus SerializeBufferBase::deserializeTo(U8* buff, Serializable::SizeType& length, Serialization::t mode) {
    FW_ASSERT(this->getBuffAddr());

    if (mode == Serialization::INCLUDE_LENGTH) {
        FwSizeStoreType storedLength;
        
        SerializeStatus stat = this->deserializeTo(storedLength);
        
        if (stat != FW_SERIALIZE_OK) {
            return stat;
        }

        // make sure it fits
        if ((storedLength > this->getBuffLeft()) or (storedLength > length)) {
            return FW_DESERIALIZE_SIZE_MISMATCH;
        }

        (void)memcpy(buff, &this->getBuffAddr()[this->m_deserLoc], static_cast<size_t>(storedLength));

        length = static_cast<FwSizeType>(storedLength);

    } else {
        // make sure enough is left
        if (length > this->getBuffLeft()) {
            return FW_DESERIALIZE_SIZE_MISMATCH;
        }

        (void)memcpy(buff, &this->getBuffAddr()[this->m_deserLoc], static_cast<size_t>(length));
    }

    this->m_deserLoc += static_cast<Serializable::SizeType>(length);
    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::deserializeTo(Serializable& val) {
    // Try new interface first, but if it returns FORMAT_ERROR (indicating default implementation),
    // fall back to old interface. This bridges auto-generated enums (old interface only) 
    // with new serialization infrastructure.
    SerializeStatus status = val.deserializeFrom(*this);
    if (status == FW_DESERIALIZE_FORMAT_ERROR) {
        // Fallback to old interface for backward compatibility
        status = val.deserialize(*this);
    }
    return status;
}

SerializeStatus SerializeBufferBase::deserializeTo(SerializeBufferBase& val) {
    FW_ASSERT(val.getBuffAddr());
    SerializeStatus stat = FW_SERIALIZE_OK;

    FwSizeStoreType storedLength;

    stat = this->deserializeTo(storedLength);

    if (stat != FW_SERIALIZE_OK) {
        return stat;
    }

    // make sure destination has enough room

    if ((storedLength > val.getBuffCapacity()) or (storedLength > this->getBuffLeft())) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }

    FW_ASSERT(this->getBuffAddr());
    (void)memcpy(val.getBuffAddr(), &this->getBuffAddr()[this->m_deserLoc], static_cast<size_t>(storedLength));

    stat = val.setBuffLen(storedLength);

    if (stat != FW_SERIALIZE_OK) {
        return stat;
    }

    this->m_deserLoc += storedLength;

    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::deserializeSize(FwSizeType& size) {
    FwSizeStoreType storedSize = 0;
    Fw::SerializeStatus status = this->deserializeTo(storedSize);
    if (status == FW_SERIALIZE_OK) {
        size = static_cast<FwSizeType>(storedSize);
    }
    return status;
}

void SerializeBufferBase::resetSer() {
    this->m_deserLoc = 0;
    this->m_serLoc = 0;
}

void SerializeBufferBase::resetDeser() {
    this->m_deserLoc = 0;
}

SerializeStatus SerializeBufferBase::serializeSkip(FwSizeType numBytesToSkip) {
    Fw::SerializeStatus status = FW_SERIALIZE_OK;
    // compute new deser loc
    const FwSizeType newSerLoc = this->m_serLoc + numBytesToSkip;
    // check for room
    if (newSerLoc <= this->getBuffCapacity()) {
        // update deser loc
        this->m_serLoc = static_cast<Serializable::SizeType>(newSerLoc);
    } else {
        status = FW_SERIALIZE_NO_ROOM_LEFT;
    }
    return status;
}

SerializeStatus SerializeBufferBase::deserializeSkip(FwSizeType numBytesToSkip) {
    // check for room
    if (this->getBuffLength() == this->m_deserLoc) {
        return FW_DESERIALIZE_BUFFER_EMPTY;
    } else if (this->getBuffLength() - this->m_deserLoc < numBytesToSkip) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }
    // update location in buffer to skip the value
    this->m_deserLoc += static_cast<Serializable::SizeType>(numBytesToSkip);
    return FW_SERIALIZE_OK;
}

SerializeStatus SerializeBufferBase::moveSerToOffset(FwSizeType offset) {
    // Reset serialization
    this->resetSer();
    // Advance to offset
    return this->serializeSkip(offset);
}
SerializeStatus SerializeBufferBase::moveDeserToOffset(FwSizeType offset) {
    // Reset deserialization
    this->resetDeser();
    // Advance to offset
    return this->deserializeSkip(offset);
}

Serializable::SizeType SerializeBufferBase::getBuffLength() const {
    return this->m_serLoc;
}

SerializeStatus SerializeBufferBase::setBuff(const U8* src, Serializable::SizeType length) {
    if (this->getBuffCapacity() < length) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    } else {
        FW_ASSERT(src);
        FW_ASSERT(this->getBuffAddr());
        (void)memcpy(this->getBuffAddr(), src, static_cast<size_t>(length));
        this->m_serLoc = length;
        this->m_deserLoc = 0;
        return FW_SERIALIZE_OK;
    }
}

SerializeStatus SerializeBufferBase::setBuffLen(Serializable::SizeType length) {
    if (this->getBuffCapacity() < length) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    } else {
        this->m_serLoc = length;
        this->m_deserLoc = 0;
        return FW_SERIALIZE_OK;
    }
}

Serializable::SizeType SerializeBufferBase::getBuffLeft() const {
    FW_ASSERT(this->m_serLoc >= this->m_deserLoc, static_cast<FwAssertArgType>(this->m_serLoc),
              static_cast<FwAssertArgType>(this->m_deserLoc));
    return this->m_serLoc - this->m_deserLoc;
}

SerializeStatus SerializeBufferBase::copyRaw(SerializeBufferBase& dest, Serializable::SizeType size) {
    // make sure there is sufficient size in destination
    if (dest.getBuffCapacity() < size) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }
    // otherwise, set destination buffer to data from deserialization pointer plus size
    SerializeStatus stat = dest.setBuff(&this->getBuffAddr()[this->m_deserLoc], size);
    if (stat == FW_SERIALIZE_OK) {
        this->m_deserLoc += size;
    }
    return stat;
}

SerializeStatus SerializeBufferBase::copyRawOffset(SerializeBufferBase& dest, Serializable::SizeType size) {
    // make sure there is sufficient size in destination
    if (dest.getBuffCapacity() < size + dest.getBuffLength()) {
        return FW_SERIALIZE_NO_ROOM_LEFT;
    }
    // make sure there is sufficient buffer in source
    if (this->getBuffLeft() < size) {
        return FW_DESERIALIZE_SIZE_MISMATCH;
    }

    // otherwise, serialize bytes to destination without writing length
    SerializeStatus stat = dest.serialize(&this->getBuffAddr()[this->m_deserLoc], size, Fw::Serialization::OMIT_LENGTH);
    if (stat == FW_SERIALIZE_OK) {
        this->m_deserLoc += size;
    }
    return stat;
}

// return address of buffer not yet deserialized. This is used
// to copy the remainder of a buffer.
const U8* SerializeBufferBase::getBuffAddrLeft() const {
    return &this->getBuffAddr()[this->m_deserLoc];
}

//!< gets address of end of serialization. Used to manually place data at the end
U8* SerializeBufferBase::getBuffAddrSer() {
    return &this->getBuffAddr()[this->m_serLoc];
}

#ifdef BUILD_UT
bool SerializeBufferBase::operator==(const SerializeBufferBase& other) const {
    if (this->getBuffLength() != other.getBuffLength()) {
        return false;
    }

    const U8* us = this->getBuffAddr();
    const U8* them = other.getBuffAddr();

    FW_ASSERT(us);
    FW_ASSERT(them);

    for (Serializable::SizeType byte = 0; byte < this->getBuffLength(); byte++) {
        if (us[byte] != them[byte]) {
            return false;
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const SerializeBufferBase& buff) {
    const U8* us = buff.getBuffAddr();

    FW_ASSERT(us);

    for (Serializable::SizeType byte = 0; byte < buff.getBuffLength(); byte++) {
        os << "[" << std::setw(2) << std::hex << std::setfill('0') << us[byte] << "]" << std::dec;
    }

    return os;
}
#endif

ExternalSerializeBuffer::ExternalSerializeBuffer(U8* buffPtr, Serializable::SizeType size) {
    this->setExtBuffer(buffPtr, size);
}

ExternalSerializeBuffer::ExternalSerializeBuffer() {
    this->clear();
}

void ExternalSerializeBuffer::setExtBuffer(U8* buffPtr, Serializable::SizeType size) {
    FW_ASSERT(buffPtr != nullptr);
    this->clear();
    this->m_buff = buffPtr;
    this->m_buffSize = size;
}

void ExternalSerializeBuffer::clear() {
    this->resetSer();
    this->resetDeser();
    this->m_buff = nullptr;
    this->m_buffSize = 0;
}

Serializable::SizeType ExternalSerializeBuffer::getBuffCapacity() const {
    return this->m_buffSize;
}

U8* ExternalSerializeBuffer::getBuffAddr() {
    return this->m_buff;
}

const U8* ExternalSerializeBuffer::getBuffAddr() const {
    return this->m_buff;
}

// ----------------------------------------------------------------------
// Deprecated method implementations for backward compatibility
// ----------------------------------------------------------------------

SerializeStatus Serializable::serialize(SerializeBufferBase& buffer) const {
    return this->serializeTo(buffer);
}

SerializeStatus Serializable::deserialize(SerializeBufferBase& buffer) {
    return this->deserializeFrom(buffer);
}

SerializeStatus SerializeBufferBase::serialize(U8 val) { return this->serializeFrom(val); }
SerializeStatus SerializeBufferBase::serialize(I8 val) { return this->serializeFrom(val); }
#if FW_HAS_16_BIT == 1
SerializeStatus SerializeBufferBase::serialize(U16 val) { return this->serializeFrom(val); }
SerializeStatus SerializeBufferBase::serialize(I16 val) { return this->serializeFrom(val); }
#endif
#if FW_HAS_32_BIT == 1
SerializeStatus SerializeBufferBase::serialize(U32 val) { return this->serializeFrom(val); }
SerializeStatus SerializeBufferBase::serialize(I32 val) { return this->serializeFrom(val); }
#endif
#if FW_HAS_64_BIT == 1
SerializeStatus SerializeBufferBase::serialize(U64 val) { return this->serializeFrom(val); }
SerializeStatus SerializeBufferBase::serialize(I64 val) { return this->serializeFrom(val); }
#endif
SerializeStatus SerializeBufferBase::serialize(F32 val) { return this->serializeFrom(val); }
SerializeStatus SerializeBufferBase::serialize(F64 val) { return this->serializeFrom(val); }
SerializeStatus SerializeBufferBase::serialize(bool val) { return this->serializeFrom(val); }
SerializeStatus SerializeBufferBase::serialize(const void* val) { return this->serializeFrom(val); }

// Deprecated method for backward compatibility
SerializeStatus SerializeBufferBase::serialize(const U8* buff, FwSizeType length, bool noLength) { 
    const Serialization::t mode = noLength ? Serialization::OMIT_LENGTH : Serialization::INCLUDE_LENGTH;
    return this->serializeFrom(buff, length, mode); 
}

SerializeStatus SerializeBufferBase::serialize(const U8* buff, FwSizeType length) { return this->serializeFrom(buff, length); }
SerializeStatus SerializeBufferBase::serialize(const U8* buff, FwSizeType length, Serialization::t mode) { return this->serializeFrom(buff, length, mode); }
SerializeStatus SerializeBufferBase::serialize(const Serializable& val) { return this->serializeFrom(val); }
SerializeStatus SerializeBufferBase::serialize(const SerializeBufferBase& val) { return this->serializeFrom(val); }

SerializeStatus SerializeBufferBase::deserialize(U8& val) { return this->deserializeTo(val); }
SerializeStatus SerializeBufferBase::deserialize(I8& val) { return this->deserializeTo(val); }
#if FW_HAS_16_BIT == 1
SerializeStatus SerializeBufferBase::deserialize(U16& val) { return this->deserializeTo(val); }
SerializeStatus SerializeBufferBase::deserialize(I16& val) { return this->deserializeTo(val); }
#endif
#if FW_HAS_32_BIT == 1
SerializeStatus SerializeBufferBase::deserialize(U32& val) { return this->deserializeTo(val); }
SerializeStatus SerializeBufferBase::deserialize(I32& val) { return this->deserializeTo(val); }
#endif
#if FW_HAS_64_BIT == 1
SerializeStatus SerializeBufferBase::deserialize(U64& val) { return this->deserializeTo(val); }
SerializeStatus SerializeBufferBase::deserialize(I64& val) { return this->deserializeTo(val); }
#endif
SerializeStatus SerializeBufferBase::deserialize(F32& val) { return this->deserializeTo(val); }
SerializeStatus SerializeBufferBase::deserialize(F64& val) { return this->deserializeTo(val); }
SerializeStatus SerializeBufferBase::deserialize(bool& val) { return this->deserializeTo(val); }
SerializeStatus SerializeBufferBase::deserialize(void*& val) { return this->deserializeTo(val); }

// Deprecated method for backward compatibility
SerializeStatus SerializeBufferBase::deserialize(U8* buff, FwSizeType& length, bool noLength) { 
    const Serialization::t mode = noLength ? Serialization::OMIT_LENGTH : Serialization::INCLUDE_LENGTH;
    return this->deserializeTo(buff, length, mode); 
}

SerializeStatus SerializeBufferBase::deserialize(U8* buff, FwSizeType& length) { 
    return this->deserializeTo(buff, length, Serialization::INCLUDE_LENGTH); 
}

SerializeStatus SerializeBufferBase::deserialize(U8* buff, FwSizeType& length, Serialization::t mode) { 
    return this->deserializeTo(buff, length, mode); 
}

SerializeStatus SerializeBufferBase::deserialize(Serializable& val) { return this->deserializeTo(val); }
SerializeStatus SerializeBufferBase::deserialize(SerializeBufferBase& val) { return this->deserializeTo(val); }

}  // namespace Fw
