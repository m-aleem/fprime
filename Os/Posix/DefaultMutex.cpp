// ======================================================================
// \title Os/Posix/DefaultMutex.cpp
// \brief sets default Os::Mutex Posix implementation via linker
// ======================================================================
#include "Os/Delegate.hpp"
#include "Os/Posix/ConditionVariable.hpp"
#include "Os/Posix/Mutex.hpp"
namespace Os {

//! \brief get a delegate for MutexInterface that intercepts calls for Posix
//! \param aligned_new_memory: aligned memory to fill
//! \return: pointer to delegate
MutexInterface* MutexInterface::getDelegate(MutexHandleStorage& aligned_new_memory) {
    return Os::Delegate::makeDelegate<MutexInterface, Os::Posix::Mutex::PosixMutex>(aligned_new_memory);
}

//! \brief get a delegate for MutexInterface that intercepts calls for Posix
//! \param aligned_new_memory: aligned memory to fill
//! \return: pointer to delegate
ConditionVariableInterface* ConditionVariableInterface::getDelegate(
    ConditionVariableHandleStorage& aligned_new_memory) {
    return Os::Delegate::makeDelegate<ConditionVariableInterface, Os::Posix::Mutex::PosixConditionVariable,
                                      ConditionVariableHandleStorage>(aligned_new_memory);
}
}  // namespace Os
