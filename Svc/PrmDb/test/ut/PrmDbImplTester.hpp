/*
 * PrmDbImplTester.hpp
 *
 *  Created on: Jun 20, 2025
 *      Author: aleem
 */

#ifndef PRMDB_TEST_UT_PRMDBTESTER_IMPL_HPP_
#define PRMDB_TEST_UT_PRMDBTESTER_IMPL_HPP_

#include <Svc/PrmDb/PrmDbImpl.hpp>

namespace Svc {

    /**
     * @brief Wrapper class for PrmDbImpl to expose private methods for testing
     *
     * This class exists to provide access to private methods of PrmDbImpl without
     * requiring additional friendship declarations. It leverages the existing
     * friendship between PrmDbImpl and PrmDbImplTester.
     */
    class PrmDbImplTester {
        public:
            /**
             * Constructor
             */
            PrmDbImplTester(PrmDbImpl& impl);

            /**
             * Destructor
             */
            virtual ~PrmDbImplTester();

            /**
             * Clear the parameter database
             */
            void clearDb();

            // /**
            //  * Access to doDispatch method
            //  */
            // Fw::QueuedComponentBase::MsgDispatchStatus doDispatch();

            /**
             * Access to readParamFile method
             */
            void readParamFile();

        private:
            PrmDbImpl& m_impl; //!< Reference to implementation being tested
    };

} /* namespace Svc */

#endif /* PRMDB_TEST_UT_PRMDBTESTER_IMPL_HPP_ */
