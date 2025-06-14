// ======================================================================
// \title Os/File.hpp
// \brief common function definitions for Os::File
// ======================================================================
#ifndef Os_File_hpp_
#define Os_File_hpp_

#include <Fw/FPrimeBasicTypes.hpp>
#include <Os/Os.hpp>

// Forward declaration for UTs
namespace Os {namespace Test {namespace FileTest {struct Tester;}}}

namespace Os {

//! \brief base implementation of FileHandle
//!
struct FileHandle {};

// This class encapsulates a very simple file interface that has the most often-used features
class FileInterface {
  public:
    enum Mode {
        OPEN_NO_MODE,     //!<  File mode not yet selected
        OPEN_READ,        //!<  Open file for reading
        OPEN_CREATE,      //!< Open file for writing and truncates file if it exists, ie same flags as creat()
        OPEN_WRITE,       //!<  Open file for writing
        OPEN_SYNC_WRITE,  //!<  Open file for writing; writes don't return until data is on disk
        OPEN_APPEND,      //!< Open file for appending
        MAX_OPEN_MODE     //!< Maximum value of mode
    };

    enum Status {
        OP_OK,              //!<  Operation was successful
        DOESNT_EXIST,       //!<  File doesn't exist (for read)
        NO_SPACE,           //!<  No space left
        NO_PERMISSION,      //!<  No permission to read/write file
        BAD_SIZE,           //!<  Invalid size parameter
        NOT_OPENED,         //!<  file hasn't been opened yet
        FILE_EXISTS,        //!< file already exist (for CREATE with O_EXCL enabled)
        NOT_SUPPORTED,      //!< Kernel or file system does not support operation
        INVALID_MODE,       //!< Mode for file access is invalid for current operation
        INVALID_ARGUMENT,   //!< Invalid argument passed in
        NO_MORE_RESOURCES,  //!< No more available resources
        OTHER_ERROR,        //!<  A catch-all for other errors. Have to look in implementation-specific code
        MAX_STATUS          //!< Maximum value of status
    };

    enum OverwriteType {
        NO_OVERWRITE,  //!< Do NOT overwrite existing files
        OVERWRITE,     //!< Overwrite file when it exists and creation was requested
        MAX_OVERWRITE_TYPE
    };

    enum SeekType {
        RELATIVE,  //!< Relative seek from current file offset
        ABSOLUTE,  //!< Absolute seek from beginning of file
        MAX_SEEK_TYPE
    };

    enum WaitType {
        NO_WAIT,  //!< Do not wait for read/write operation to finish
        WAIT,     //!< Do wait for read/write operation to finish
        MAX_WAIT_TYPE
    };

    virtual ~FileInterface() = default;

    //! \brief open file with supplied path and mode
    //!
    //! Open the file passed in with the given mode. If overwrite is set to OVERWRITE, then opening files in
    //! OPEN_CREATE mode will clobber existing files. Set overwrite to NO_OVERWRITE to preserve existing files.
    //! The status of the open request is returned from the function call. Delegates to the chosen
    //! implementation's `open` function.
    //!
    //! It is invalid to send `nullptr` as the path.
    //! It is invalid to supply `mode` as a non-enumerated value.
    //! It is invalid to supply `overwrite` as a non-enumerated value.
    //!
    //! \param path: c-string of path to open
    //! \param mode: file operation mode
    //! \param overwrite: overwrite existing file on create
    //! \return: status of the open
    //!
    virtual Status open(const char* path, Mode mode, OverwriteType overwrite) = 0;

    //! \brief close the file, if not opened then do nothing
    //!
    //! Closes the file, if open. Otherwise this function does nothing. Delegates to the chosen implementation's
    //! `closeInternal` function. `mode` is set to `OPEN_NO_MODE`.
    //!
    virtual void close() = 0;

    //! \brief get size of currently open file
    //!
    //! Get the size of the currently open file and fill the size parameter. Return status of the operation.
    //! \param size: output parameter for size.
    //! \return OP_OK on success otherwise error status
    //!
    virtual Status size(FwSizeType& size_result) = 0;

    //! \brief get file pointer position of the currently open file
    //!
    //! Get the current position of the read/write pointer of the open file.
    //! \param position: output parameter for size.
    //! \return OP_OK on success otherwise error status
    //!
    virtual Status position(FwSizeType& position_result) = 0;

    //! \brief pre-allocate file storage
    //!
    //! Pre-allocates file storage with at least `length` storage starting at `offset`. No-op on implementations
    //! that cannot pre-allocate.
    //!
    //! It is invalid to pass a negative `offset`.
    //! It is invalid to pass a negative `length`.
    //!
    //! \param offset: offset into file
    //! \param length: length after offset to preallocate
    //! \return OP_OK on success otherwise error status
    //!
    virtual Status preallocate(FwSizeType offset, FwSizeType length) = 0;

    //! \brief seek the file pointer to the given offset
    //!
    //! Seek the file pointer to the given `offset`. If `seekType` is set to `ABSOLUTE` then the offset is calculated
    //! from the start of the file, and if it is set to `RELATIVE` it is calculated from the current position.
    //!
    //! \param offset: offset to seek to
    //! \param seekType: `ABSOLUTE` for seeking from beginning of file, `RELATIVE` to use current position.
    //! \return OP_OK on success otherwise error status
    //!
    virtual Status seek(FwSignedSizeType offset, SeekType seekType) = 0;

    //! \brief flush file contents to storage
    //!
    //! Flushes the file contents to storage (i.e. out of the OS cache to disk). Does nothing in implementations
    //! that do not support flushing.
    //!
    //! \return OP_OK on success otherwise error status
    //!
    virtual Status flush() = 0;

    //! \brief read data from this file into supplied buffer bounded by size
    //!
    //! Read data from this file up to the `size` and store it in `buffer`.  When `wait` is set to `WAIT`, this
    //! will block until the requested size has been read successfully read or the end of the file has been
    //! reached. When `wait` is set to `NO_WAIT` it will return whatever data is currently available.
    //!
    //! `size` will be updated to the count of bytes actually read. Status will reflect the success/failure of
    //! the read operation.
    //!
    //! It is invalid to pass `nullptr` to this function call.
    //! It is invalid to pass a negative `size`.
    //! It is invalid to supply wait as a non-enumerated value.
    //!
    //! \param buffer: memory location to store data read from file
    //! \param size: size of data to read
    //! \param wait: `WAIT` to wait for data, `NO_WAIT` to return what is currently available
    //! \return OP_OK on success otherwise error status
    //!
    virtual Status read(U8* buffer, FwSizeType& size, WaitType wait) = 0;

    //! \brief read data from this file into supplied buffer bounded by size
    //!
    //! Write data to this file up to the `size` from the `buffer`.  When `wait` is set to `WAIT`, this
    //! will block until the requested size has been written successfully to disk. When `wait` is set to
    //! `NO_WAIT` it will return once the data is sent to the OS.
    //!
    //! `size` will be updated to the count of bytes actually written. Status will reflect the success/failure of
    //! the read operation.
    //!
    //! It is invalid to pass `nullptr` to this function call.
    //! It is invalid to pass a negative `size`.
    //! It is invalid to supply wait as a non-enumerated value.
    //!
    //! \param buffer: memory location to store data read from file
    //! \param size: size of data to read
    //! \param wait: `WAIT` to wait for data to write to disk, `NO_WAIT` to return what is currently available
    //! \return OP_OK on success otherwise error status
    //!
    virtual Status write(const U8* buffer, FwSizeType& size, WaitType wait) = 0;

    //! \brief returns the raw file handle
    //!
    //! Gets the raw file handle from the implementation. Note: users must include the implementation specific
    //! header to make any real use of this handle. Otherwise it will be as an opaque type.
    //!
    //! \return raw file handle
    //!
    virtual FileHandle* getHandle() = 0;

    //! \brief provide a pointer to a file delegate object
    //!
    //! This function must return a pointer to a `FileInterface` object that contains the real implementation of the
    //! file functions as defined by the implementor.  This function must do several things to be considered correctly
    //! implemented:
    //!
    //! 1. Assert that the supplied memory is non-null. e.g `FW_ASSERT(aligned_placement_new_memory != NULL);`
    //! 2. Assert that their implementation fits within FW_HANDLE_MAX_SIZE.
    //!    e.g. `static_assert(sizeof(PosixFileImplementation) <= sizeof Os::File::m_handle_storage,
    //!        "FW_HANDLE_MAX_SIZE too small");`
    //! 3. Assert that their implementation aligns within FW_HANDLE_ALIGNMENT.
    //!    e.g. `static_assert((FW_HANDLE_ALIGNMENT % alignof(PosixFileImplementation)) == 0, "Bad handle alignment");`
    //! 4. If to_copy is null, placement new their implementation into `aligned_placement_new_memory`
    //!    e.g. `FileInterface* interface = new (aligned_placement_new_memory) PosixFileImplementation;`
    //! 5. If to_copy is non-null, placement new using copy constructor their implementation into
    //!    `aligned_placement_new_memory`
    //!    e.g. `FileInterface* interface = new (aligned_placement_new_memory) PosixFileImplementation(*to_copy);`
    //! 6. Return the result of the placement new
    //!    e.g. `return interface;`
    //!
    //! \return result of placement new, must be equivalent to `aligned_placement_new_memory`
    //!
    static FileInterface* getDelegate(FileHandleStorage& aligned_placement_new_memory,
                                      const FileInterface* to_copy = nullptr);
};

class File final : public FileInterface {

  friend struct Os::Test::FileTest::Tester;

  public:
    //! \brief constructor
    //!
    File();
    //! \brief destructor
    //!
    //! Destructor closes the file if it is open
    ~File() final;

    //! \brief copy constructor that copies the internal representation
    File(const File& other);

    //! \brief assignment operator that copies the internal representation
    File& operator=(const File& other);

    //! \brief determine if the file is open
    //! \return true if file is open, false otherwise
    //!
    bool isOpen() const;

    // ------------------------------------
    // Functions supplying default values
    // ------------------------------------

    //! \brief open file with supplied path and mode
    //!
    //! Open the file passed in with the given mode. Opening files with `OPEN_CREATE` mode will not clobber existing
    //! files. Use other `open` method to set overwrite flag and clobber existing files. The status of the open
    //! request is returned from the function call. Delegates to the chosen implementation's `open` function.
    //!
    //! It is invalid to send `nullptr` as the path.
    //! It is invalid to supply `mode` as a non-enumerated value.
    //!
    //! \param path: c-string of path to open
    //! \param mode: file operation mode
    //! \return: status of the open
    //!
    Os::FileInterface::Status open(const char* path, Mode mode);

    //! \brief read data from this file into supplied buffer bounded by size
    //!
    //! Read data from this file up to the `size` and store it in `buffer`.  This version will
    //! will block until the requested size has been read successfully read or the end of the file has been
    //! reached.
    //!
    //! `size` will be updated to the count of bytes actually read. Status will reflect the success/failure of
    //! the read operation.
    //!
    //! It is invalid to pass `nullptr` to this function call.
    //! It is invalid to pass a negative `size`.
    //!
    //! \param buffer: memory location to store data read from file
    //! \param size: size of data to read
    //! \return OP_OK on success otherwise error status
    //!
    Status read(U8* buffer, FwSizeType& size);

    //! \brief write data to this file from the supplied buffer bounded by size
    //!
    //! Write data from `buffer` up to the `size` and store it in this file. This call
    //! will block until the requested size has been written. Otherwise, this call will write without blocking.
    //!
    //! `size` will be updated to the count of bytes actually written. Status will reflect the success/failure of
    //! the write operation.
    //!
    //! It is invalid to pass `nullptr` to this function call.
    //! It is invalid to pass a negative `size`.
    //!
    //! \param buffer: memory location of data to write to file
    //! \param size: size of data to write
    //! \return OP_OK on success otherwise error status
    //!
    Status write(const U8* buffer, FwSizeType& size);

    // ------------------------------------
    // Functions overrides
    // ------------------------------------

    //! \brief open file with supplied path and mode
    //!
    //! Open the file passed in with the given mode. If overwrite is set to OVERWRITE, then opening files in
    //! OPEN_CREATE mode will clobber existing files. Set overwrite to NO_OVERWRITE to preserve existing files.
    //! The status of the open request is returned from the function call. Delegates to the chosen
    //! implementation's `open` function.
    //!
    //! It is invalid to send `nullptr` as the path.
    //! It is invalid to supply `mode` as a non-enumerated value.
    //! It is invalid to supply `overwrite` as a non-enumerated value.
    //!
    //! \param path: c-string of path to open
    //! \param mode: file operation mode
    //! \param overwrite: overwrite existing file on create
    //! \return: status of the open
    //!
    Os::FileInterface::Status open(const char* path, Mode mode, OverwriteType overwrite) override;

    //! \brief close the file, if not opened then do nothing
    //!
    //! Closes the file, if open. Otherwise this function does nothing. Delegates to the chosen implementation's
    //! `closeInternal` function. `mode` is set to `OPEN_NO_MODE`.
    //!
    void close() override;

    //! \brief get size of currently open file
    //!
    //! Get the size of the currently open file and fill the size parameter. Return status of the operation.
    //! \param size: output parameter for size.
    //! \return OP_OK on success otherwise error status
    //!
    Status size(FwSizeType& size_result) override;

    //! \brief get file pointer position of the currently open file
    //!
    //! Get the current position of the read/write pointer of the open file.
    //! \param position: output parameter for size.
    //! \return OP_OK on success otherwise error status
    //!
    Status position(FwSizeType& position_result) override;

    //! \brief pre-allocate file storage
    //!
    //! Pre-allocates file storage with at least `length` storage starting at `offset`. No-op on implementations
    //! that cannot pre-allocate.
    //!
    //! It is invalid to pass a negative `offset`.
    //! It is invalid to pass a negative `length`.
    //!
    //! \param offset: offset into file
    //! \param length: length after offset to preallocate
    //! \return OP_OK on success otherwise error status
    //!
    Status preallocate(FwSizeType offset, FwSizeType length) override;

    //! \brief seek the file pointer to the given offset
    //!
    //! Seek the file pointer to the given `offset`. If `seekType` is set to `ABSOLUTE` then the offset is calculated
    //! from the start of the file, and if it is set to `RELATIVE` it is calculated from the current position.
    //!
    //! \param offset: offset to seek to
    //! \param seekType: `ABSOLUTE` for seeking from beginning of file, `RELATIVE` to use current position.
    //! \return OP_OK on success otherwise error status
    //!
    Status seek(FwSignedSizeType offset, SeekType seekType) override;

    //! \brief seek the file pointer to the given offset absolutely with the full range
    //!
    //! Seek the file pointer to the given `offset` absolutely from the beginning of the file. This function is
    //! equivalent to calling `seek` with `ABSOLUTE` as the `seekType` with the exception that it can handle the
    //! full range of `FwSizeType` values as returned by `size` and `position` calls.
    //!
    //! Internally, it will perform multiple seeks to reach the desired offset while never exceeding the signed
    //! limit of the basic `seek` function.
    //!
    //! \param offset_unsigned: offset to absolutely seek to
    //! \return OP_OK on success otherwise error status
    Status seek_absolute(FwSizeType offset_unsigned);

    //! \brief flush file contents to storage
    //!
    //! Flushes the file contents to storage (i.e. out of the OS cache to disk). Does nothing in implementations
    //! that do not support flushing.
    //!
    //! \return OP_OK on success otherwise error status
    //!
    Status flush() override;

    //! \brief read data from this file into supplied buffer bounded by size
    //!
    //! Read data from this file up to the `size` and store it in `buffer`.  When `wait` is set to `WAIT`, this
    //! will block until the requested size has been read successfully read or the end of the file has been
    //! reached. When `wait` is set to `NO_WAIT` it will return whatever data is currently available.
    //!
    //! `size` will be updated to the count of bytes actually read. Status will reflect the success/failure of
    //! the read operation.
    //!
    //! It is invalid to pass `nullptr` to this function call.
    //! It is invalid to pass a negative `size`.
    //! It is invalid to supply wait as a non-enumerated value.
    //!
    //! \param buffer: memory location to store data read from file
    //! \param size: size of data to read
    //! \param wait: `WAIT` to wait for data, `NO_WAIT` to return what is currently available

    //!
    Status read(U8* buffer, FwSizeType& size, WaitType wait) override;

    //! \brief read a line from the file using `\n` as the delimiter
    //!
    //! Reads a single line from the file including the terminating '\n'. This will return an error if no line is
    //! found within the specified buffer size. In the case of EOF, the line is read without the terminating '\n'.
    //!
    //! In the case of an error, this function will seek to the original location in the file. Otherwise, the
    //! pointer will point to the first character after the `\n` or EOF in the case of no `\n`.
    //!
    //! It is invalid to send a null buffer.
    //! It is invalid to send a size less than 0.
    //! It is an error if the file is not opened for reading.
    //!
    //! \param buffer: memory location to store data read from file
    //! \param size: maximum size of buffer to store the new line
    //! \param wait: `WAIT` to wait for data, `NO_WAIT` to return what is currently available
    //! \return OP_OK on success otherwise error status
    Status readline(U8* buffer, FwSizeType& size, WaitType wait);

    //! \brief read data from this file into supplied buffer bounded by size
    //!
    //! Write data to this file up to the `size` from the `buffer`.  When `wait` is set to `WAIT`, this
    //! will block until the requested size has been written successfully to disk. When `wait` is set to
    //! `NO_WAIT` it will return once the data is sent to the OS.
    //!
    //! `size` will be updated to the count of bytes actually written. Status will reflect the success/failure of
    //! the read operation.
    //!
    //! It is invalid to pass `nullptr` to this function call.
    //! It is invalid to pass a negative `size`.
    //! It is invalid to supply wait as a non-enumerated value.
    //!
    //! \param buffer: memory location to store data read from file
    //! \param size: size of data to read
    //! \param wait: `WAIT` to wait for data to write to disk, `NO_WAIT` to return what is currently available
    //! \return OP_OK on success otherwise error status
    //!
    Status write(const U8* buffer, FwSizeType& size, WaitType wait) override;

    //! \brief returns the raw file handle
    //!
    //! Gets the raw file handle from the implementation. Note: users must include the implementation specific
    //! header to make any real use of this handle. Otherwise it//!must* be passed as an opaque type.
    //!
    //! \return raw file handle
    //!
    FileHandle* getHandle() override;

    //! \brief calculate the CRC32 of the entire file
    //!
    //! Calculates the CRC32 of the file's contents. The `crc` parameter will be updated to contain the CRC or 0 on
    //! failure. Status will represent failure conditions. This call will be decomposed into calculations on
    //! sections of the file `FW_FILE_CHUNK_SIZE` bytes long.
    //!
    //! This function requires that the file already be opened for "READ" mode.
    //!
    //! On error crc will be set to 0.
    //!
    //! \note: the file pointer will be positioned at the end of the file after this call.
    //!
    //! This function is equivalent to the following pseudo-code:
    //!
    //! ```
    //! U32 crc;
    //! do {
    //!     size = FW_FILE_CHUNK_SIZE;
    //!     m_file.incrementalCrc(size);
    //! while (size == FW_FILE_CHUNK_SIZE);
    //! m_file.finalize(crc);
    //! ```
    //! \param crc: U32 bit value to fill with CRC
    //! \return OP_OK on success otherwise error status
    //!
    Status calculateCrc(U32& crc);

    //! \brief calculate the CRC32 of the next section of data
    //!
    //! Starting at the current file pointer, this will add `size` bytes of data to the currently calculated CRC.
    //! Call `finalizeCrc` to retrieve the CRC or `calculateCrc` to perform a CRC on the entire file. This call will
    //! not block waiting for data on the underlying read, nor will it reset the file position pointer. On error,
    //! the current CRC results should be discarded by reopening the file or calling `finalizeCrc` and
    //! discarding its result. `size` will be updated with the `size` actually read and used in the CRC calculation.
    //!
    //! This function requires that the file already be opened for "READ" mode.
    //!
    //! It is illegal for size to be less than or equal to 0 or greater than FW_FILE_CHUNK_SIZE.
    //!
    //! \param size: size of data to read for CRC
    //! \return: status of the CRC calculation
    //!
    Status incrementalCrc(FwSizeType& size);

    //! \brief finalize and retrieve the CRC value
    //!
    //! Finalizes the CRC computation and returns the CRC value. The `crc` value will be modified to contain the
    //! crc or 0 on error. Note: this will reset any active CRC calculation and effectively re-initializes any
    //! `incrementalCrc` calculation.
    //!
    //! On error crc will be set to 0.
    //!
    //! \param crc: value to fill
    //! \return status of the CRC calculation
    //!
    Status finalizeCrc(U32& crc);

  private:
    static const U32 INITIAL_CRC = 0xFFFFFFFF;            //!< Initial value for CRC calculation

    Mode m_mode = Mode::OPEN_NO_MODE;                     //!< Stores mode for error checking
    const CHAR* m_path = nullptr;                         //!< Path last opened

    U32 m_crc = File::INITIAL_CRC;  //!< Current CRC calculation
    U8 m_crc_buffer[FW_FILE_CHUNK_SIZE];

    // This section is used to store the implementation-defined file handle. To Os::File and fprime, this type is
    // opaque and thus normal allocation cannot be done. Instead, we allow the implementor to store then handle in
    // the byte-array here and set `handle` to that address for storage.
    //
    alignas(FW_HANDLE_ALIGNMENT) FileHandleStorage m_handle_storage;  //!< Storage for aligned FileHandle data
    FileInterface& m_delegate;                                        //!< Delegate for the real implementation
};
}  // namespace Os
#endif
