// ======================================================================
// \title Os/Posix/Mutex.cpp
// \brief Posix implementation for Os::Mutex
// ======================================================================
#include <Fw/Types/Assert.hpp>
#include <Os/Posix/Mutex.hpp>
#include <Os/Posix/error.hpp>

namespace Os {
namespace Posix {
namespace Mutex {

PosixMutex::PosixMutex() : Os::MutexInterface(), m_handle() {
    // set attributes
    pthread_mutexattr_t attribute;
    int status = pthread_mutexattr_init(&attribute);
    FW_ASSERT(status == 0, static_cast<FwAssertArgType>(status));

    // set to normal mutex type
    status = pthread_mutexattr_settype(&attribute, PTHREAD_MUTEX_ERRORCHECK);
    FW_ASSERT(status == 0, static_cast<FwAssertArgType>(status));

    // set to check for priority inheritance
    status = pthread_mutexattr_setprotocol(&attribute, PTHREAD_PRIO_INHERIT);
    FW_ASSERT(status == 0, static_cast<FwAssertArgType>(status));

    status = pthread_mutex_init(&this->m_handle.m_mutex_descriptor, &attribute);
    FW_ASSERT(status == 0, static_cast<FwAssertArgType>(status));
}

PosixMutex::~PosixMutex() {
    int status = pthread_mutex_destroy(&this->m_handle.m_mutex_descriptor);
    FW_ASSERT(status == 0, static_cast<FwAssertArgType>(status));
}

PosixMutex::Status PosixMutex::take() {
    int status = pthread_mutex_lock(&this->m_handle.m_mutex_descriptor);
    return Os::Posix::posix_status_to_mutex_status(status);
}

PosixMutex::Status PosixMutex::release() {
    int status = pthread_mutex_unlock(&this->m_handle.m_mutex_descriptor);
    return Os::Posix::posix_status_to_mutex_status(status);
}

MutexHandle* PosixMutex::getHandle() {
    return &this->m_handle;
}
}  // namespace Mutex
}  // namespace Posix
}  // namespace Os
