// ======================================================================
// \title  CRCChecker.cpp
// \author ortega
// \brief  cpp file for a crc32 checker
//
// \copyright
// Copyright 2009-2020, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include <Fw/FPrimeBasicTypes.hpp>
#include <Utils/CRCChecker.hpp>
#include <Fw/Types/Assert.hpp>
#include <Os/File.hpp>
#include <Os/FileSystem.hpp>
#include <Utils/Hash/Hash.hpp>
#include <Fw/Types/FileNameString.hpp>

namespace Utils {
static_assert(FW_USE_PRINTF_FAMILY_FUNCTIONS_IN_STRING_FORMATTING,
        "Cannot use CRC checker without full string formatting");

  crc_stat_t create_checksum_file(const char* const fname)
  {
    FW_ASSERT(fname != nullptr);

    FwSizeType i;
    FwSizeType blocks;
    FwSizeType remaining_bytes;
    FwSizeType filesize;
    Os::File f;
    Os::FileSystem::Status fs_stat;
    Os::File::Status stat;
    Utils::Hash hash;
    U32 checksum;
    FwSizeType bytes_to_read;
    FwSizeType bytes_to_write;
    Fw::FileNameString hashFilename;
    U8 block_data[CRC_FILE_READ_BLOCK];

    fs_stat = Os::FileSystem::getFileSize(fname, filesize);
    if(fs_stat != Os::FileSystem::OP_OK)
    {
      return FAILED_FILE_SIZE;
    }

    // Open file
    stat = f.open(fname, Os::File::OPEN_READ);
    if(stat != Os::File::OP_OK)
    {
      return FAILED_FILE_OPEN;
    }

    // Read file
    bytes_to_read = CRC_FILE_READ_BLOCK;
    blocks = filesize / CRC_FILE_READ_BLOCK;
    for(i = 0; i < blocks; i++)
    {
      stat = f.read(block_data, bytes_to_read);
      if(stat != Os::File::OP_OK || bytes_to_read != CRC_FILE_READ_BLOCK)
      {
        f.close();
        return  FAILED_FILE_READ;
      }

      hash.update(block_data, bytes_to_read);
    }

    remaining_bytes = filesize % CRC_FILE_READ_BLOCK;
    bytes_to_read = remaining_bytes;
    if(remaining_bytes > 0)
    {
      stat = f.read(block_data, bytes_to_read);
      if(stat != Os::File::OP_OK || bytes_to_read != remaining_bytes)
      {
        f.close();
        return FAILED_FILE_READ;
      }

      hash.update(block_data, remaining_bytes);
    }

    // close file
    f.close();

    // generate checksum
    hash.final(checksum);

    // open checksum file
    Fw::FormatStatus formatStatus = hashFilename.format("%s%s", fname, HASH_EXTENSION_STRING);
    FW_ASSERT(formatStatus == Fw::FormatStatus::SUCCESS);

    stat = f.open(hashFilename.toChar(), Os::File::OPEN_WRITE);
    if(stat != Os::File::OP_OK)
    {
      return FAILED_FILE_CRC_OPEN;
    }

    // Write  checksum  file
    bytes_to_write = sizeof(checksum);
    stat = f.write(reinterpret_cast<U8*>(&checksum), bytes_to_write);
    if(stat != Os::File::OP_OK || sizeof(checksum) != bytes_to_write)
    {
      f.close();
      return FAILED_FILE_CRC_WRITE;
    }

    // close checksum file
    f.close();

    return PASSED_FILE_CRC_WRITE;
  }

  crc_stat_t read_crc32_from_file(const char* const fname, U32 &checksum_from_file) {
      Os::File f;
      Os::File::Status stat;
      Fw::FileNameString hashFilename;
      FW_ASSERT(fname != nullptr);
      // open checksum file
      Fw::FormatStatus formatStatus = hashFilename.format("%s%s", fname, HASH_EXTENSION_STRING);
      FW_ASSERT(formatStatus == Fw::FormatStatus::SUCCESS);

      stat = f.open(hashFilename.toChar(), Os::File::OPEN_READ);
      if(stat != Os::File::OP_OK)
      {
        return FAILED_FILE_CRC_OPEN;
      }

      // Read  checksum  file
      FwSizeType checksum_from_file_size = static_cast<FwSizeType>(sizeof(checksum_from_file));
      stat = f.read(reinterpret_cast<U8*>(&checksum_from_file), checksum_from_file_size);
      if(stat != Os::File::OP_OK || checksum_from_file_size != sizeof(checksum_from_file))
      {
        f.close();
        return FAILED_FILE_CRC_READ;
      }

      // close checksum file
      f.close();
      return PASSED_FILE_CRC_CHECK;
  }

  crc_stat_t verify_checksum(const char* const fname, U32 &expected, U32 &actual)
  {
    FW_ASSERT(fname != nullptr);

    FwSizeType i;
    FwSizeType blocks;
    FwSizeType remaining_bytes;
    FwSizeType filesize;
    Os::File f;
    Os::FileSystem::Status fs_stat;
    Os::File::Status stat;
    Utils::Hash hash;
    U32 checksum;
    U32 checksum_from_file;
    FwSizeType bytes_to_read;
    U8 block_data[CRC_FILE_READ_BLOCK];

    fs_stat = Os::FileSystem::getFileSize(fname, filesize);
    if(fs_stat != Os::FileSystem::OP_OK)
    {
      return FAILED_FILE_SIZE;
    }

    // Open file
    stat = f.open(fname, Os::File::OPEN_READ);
    if(stat != Os::File::OP_OK)
    {
      return FAILED_FILE_OPEN;
    }

    // Read file
    bytes_to_read = CRC_FILE_READ_BLOCK;
    blocks = filesize / CRC_FILE_READ_BLOCK;
    for(i = 0; i < blocks; i++)
    {
      stat = f.read(block_data, bytes_to_read);
      if(stat != Os::File::OP_OK || bytes_to_read != CRC_FILE_READ_BLOCK)
      {
        f.close();
        return  FAILED_FILE_READ;
      }

      hash.update(block_data, static_cast<FwSizeType>(bytes_to_read));
    }

    remaining_bytes = filesize % CRC_FILE_READ_BLOCK;
    bytes_to_read = remaining_bytes;
    if(remaining_bytes > 0)
    {
      stat = f.read(block_data, bytes_to_read);
      if(stat != Os::File::OP_OK || bytes_to_read != remaining_bytes)
      {
        f.close();
        return FAILED_FILE_READ;
      }

      hash.update(block_data, remaining_bytes);
    }

    // close file
    f.close();
    // generate checksum
    hash.final(checksum);

    crc_stat_t crcstat = read_crc32_from_file(fname, checksum_from_file);
    if (crcstat != PASSED_FILE_CRC_CHECK) {
        return crcstat;
    }

    // compare checksums
    if(checksum != checksum_from_file)
    {
      expected = checksum_from_file;
      actual = checksum;
      return FAILED_FILE_CRC_CHECK;
    }

    expected = checksum_from_file;
    actual = checksum;
    return PASSED_FILE_CRC_CHECK;
  }

}
