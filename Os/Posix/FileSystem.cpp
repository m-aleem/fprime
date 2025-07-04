// ======================================================================
// \title Os/Posix/FileSystem.cpp
// \brief Posix implementation for Os::FileSystem
// ======================================================================
#include "Os/Posix/FileSystem.hpp"
#include "Os/Posix/error.hpp"

#include <dirent.h>
#ifndef TGT_OS_TYPE_VXWORKS
#include <sys/statvfs.h>
#endif
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>

#include <cerrno>

namespace Os {
namespace Posix {
namespace FileSystem {

PosixFileSystem::Status PosixFileSystem::_removeDirectory(const char* path) {
    Status status = OP_OK;
    if (::rmdir(path) == -1) {
        status = errno_to_filesystem_status(errno);
    }
    return status;
}

PosixFileSystem::Status PosixFileSystem::_removeFile(const char* path) {
    Status status = OP_OK;
    if (::unlink(path) == -1) {
        status = errno_to_filesystem_status(errno);
    }
    return status;
}

PosixFileSystem::Status PosixFileSystem::_rename(const char* originPath, const char* destPath) {
    Status status = OP_OK;
    if (::rename(originPath, destPath) == -1) {
        status = errno_to_filesystem_status(errno);
    }
    return status;
}

PosixFileSystem::Status PosixFileSystem::_getWorkingDirectory(char* path, FwSizeType bufferSize) {
    Status status = OP_OK;
    if (::getcwd(path, static_cast<size_t>(bufferSize)) == nullptr) {
        status = errno_to_filesystem_status(errno);
    }
    return status;
}

PosixFileSystem::Status PosixFileSystem::_changeWorkingDirectory(const char* path) {
    Status status = OP_OK;
    if (::chdir(path) == -1) {
        status = errno_to_filesystem_status(errno);
    }
    return status;
}

PosixFileSystem::Status PosixFileSystem::_getFreeSpace(const char* path,
                                                       FwSizeType& totalBytes,
                                                       FwSizeType& freeBytes) {
#ifdef TGT_OS_TYPE_VXWORKS
    return Status::NOT_SUPPORTED;
#else
    Status stat = OP_OK;
    static_assert(std::numeric_limits<FwSizeType>::max() >= std::numeric_limits<fsblkcnt_t>::max(),
                  "FwSizeType must be able to hold fsblkcnt_t");
    static_assert(std::numeric_limits<FwSizeType>::min() <= std::numeric_limits<fsblkcnt_t>::min(),
                  "FwSizeType must be able to hold fsblkcnt_t");
    static_assert(std::numeric_limits<FwSizeType>::max() >= std::numeric_limits<unsigned long>::max(),
                  "FwSizeType must be able to hold unsigned long");
    struct statvfs fsStat;
    int ret = statvfs(path, &fsStat);
    if (ret) {
        return errno_to_filesystem_status(errno);
    }

    const FwSizeType block_size = static_cast<FwSizeType>(fsStat.f_frsize);
    const FwSizeType free_blocks = static_cast<FwSizeType>(fsStat.f_bfree);
    const FwSizeType total_blocks = static_cast<FwSizeType>(fsStat.f_blocks);

    // Check for overflow in multiplication
    if (free_blocks > (std::numeric_limits<FwSizeType>::max() / block_size) ||
        total_blocks > (std::numeric_limits<FwSizeType>::max() / block_size)) {
        return OVERFLOW_ERROR;
    }
    freeBytes = free_blocks * block_size;
    totalBytes = total_blocks * block_size;
    return stat;
#endif
}

FileSystemHandle* PosixFileSystem::getHandle() {
    return &this->m_handle;
}

PosixFileSystem::Status PosixFileSystem::_getPathType(const char* path, PathType& pathType) {
    FW_ASSERT(path != nullptr);
    struct stat path_stat;
    const I32 status = lstat(path, &path_stat);
    if (status == 0) {
        if (S_ISDIR(path_stat.st_mode)) {
            pathType = PathType::DIRECTORY;
        } else if (S_ISREG(path_stat.st_mode)) {
            pathType = PathType::FILE;
        } else {
            pathType = PathType::OTHER;
        }
        return Status::OP_OK;
    } else {
        return errno_to_filesystem_status(errno);
    }
}

}  // namespace FileSystem
}  // namespace Posix
}  // namespace Os
