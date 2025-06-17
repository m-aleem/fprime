// ======================================================================
// \title  DpContainerTester.hpp
// \author m-aleem
// \brief  hpp file for DpContainerTester
// ======================================================================

#ifndef Fw_DpContainerTester_HPP
#define Fw_DpContainerTester_HPP

#include "Fw/Dp/DpContainer.hpp"

namespace Types {

    class DpContainerTester {

        public:

            static FwSizeType tester_get_m_dataBuffer_getSize(Fw::DpContainer& container){
                return container.m_buffer.getSize();
            }

            static FwSizeType tester_get_m_dataBuffer_getBuffCapacity(Fw::DpContainer& container){
                return container.m_dataBuffer.getBuffCapacity();
            }

            static U8* tester_get_m_dataBuffer_getBuffAddr(Fw::DpContainer& container){
                return container.m_dataBuffer.getBuffAddr();
            }

            static U8* tester_get_m_buffer_getData(Fw::DpContainer& container){
                return container.m_buffer.getData();
            }
    };

}

#endif
