/*
 * PrmDbImplTester.cpp
 *
 *  Created on: Jun 20, 2025
 *      Author: aleem
 */

#include <Svc/PrmDb/test/ut/PrmDbImplTester.hpp>

namespace Svc {

    PrmDbImplTester::PrmDbImplTester(PrmDbImpl& impl) :
        m_impl(impl) {
    }

    PrmDbImplTester::~PrmDbImplTester() {
    }

    void PrmDbImplTester::clearDb() {
        // Access private method through friendship
        this->m_impl.clearDb();
    }

    // Fw::QueuedComponentBase::MsgDispatchStatus PrmDbImplTester::doDispatch() {
    //     // Access private method through friendship
    //     return this->m_impl.doDispatch();
    // }

    void PrmDbImplTester::readParamFile() {
        // Access private method through friendship
        this->m_impl.readParamFile();
    }
} /* namespace Svc */
