// ======================================================================
// \title  UdpSocket.hpp
// \author mstarch
// \brief  hpp file for UdpSocket core implementation classes
//
// \copyright
// Copyright 2009-2020, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================
#ifndef DRV_IP_UDPSOCKET_HPP_
#define DRV_IP_UDPSOCKET_HPP_

#include <Fw/FPrimeBasicTypes.hpp>
#include <Drv/Ip/IpSocket.hpp>
#include <config/IpCfg.hpp>

// Include system headers for sockaddr_in
#ifdef TGT_OS_TYPE_VXWORKS
    #include <socket.h>
    #include <inetLib.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

namespace Drv {

/**
 * \brief Helper for setting up Udp using Berkeley sockets as a client
 *
 * Certain IP headers have conflicting definitions with the m_data member of various types in fprime. UdpSocket
 * separates the ip setup from the incoming Fw::Buffer in the primary component class preventing this collision.
 */
class UdpSocket : public IpSocket {
  public:
    /**
     * \brief Constructor for client socket udp implementation
     */
    UdpSocket();
    /**
     * \brief to cleanup state created at instantiation
     */
    virtual ~UdpSocket();

    /**
     * \brief configure is disabled
     *
     * \warning configure is disabled for UdpSocket. Use configureSend and configureRecv instead.
     */
    SocketIpStatus configure(const char* hostname, const U16 port, const U32 send_timeout_seconds,
                             const U32 send_timeout_microseconds) override;

    /**
     * \brief configure the udp socket for outgoing transmissions
     *
     * Configures the UDP handler to use the given hostname and port for outgoing transmissions. Incoming hostname
     * and port are configured using the `configureRecv` function call for UDP as it requires separate host/port pairs
     * for outgoing and incoming transmissions. Hostname DNS translation is left up to the caller and thus hostname must
     * be an IP address in dot-notation of the form "x.x.x.x". If port is set to 0, the socket will be configured for
     * ephemeral send (dynamic reply-to) and will use the sender's address from the first received datagram for replies.
     * It is possible to configure the UDP port as a single-direction send port only.
     *
     * Note: delegates to `IpSocket::configure`
     *
     * \param hostname: socket uses for outgoing transmissions. Must be of form x.x.x.x
     * \param port: port socket uses for outgoing transmissions. Can be 0 for ephemeral reply-to mode.
     * \param send_timeout_seconds: send timeout seconds portion
     * \param send_timeout_microseconds: send timeout microseconds portion. Must be less than 1000000
     * \return status of configure
     */
    SocketIpStatus configureSend(const char* hostname, const U16 port, const U32 send_timeout_seconds,
                                 const U32 send_timeout_microseconds);

    /**
     * \brief configure the udp socket for incoming transmissions
     *
     * Configures the UDP handler to use the given hostname and port for incoming transmissions. Outgoing hostname
     * and port are configured using the `configureSend` function call for UDP as it requires separate host/port pairs
     * for outgoing and incoming transmissions. Hostname DNS translation is left up to the caller and thus hostname must
     * be an IP address in dot-notation of the form "x.x.x.x". It is possible to configure the UDP port as a
     * single-direction receive port only.
     *
     * \param hostname: socket uses for incoming transmissions. Must be of form x.x.x.x
     * \param port: port socket uses for incoming transmissions. Can be 0 for ephemeral port assignment.
     * \return status of configure
     */
    SocketIpStatus configureRecv(const char* hostname, const U16 port);

    /**
     * \brief get the port being received on
     *
     * Most useful when receive was configured to use port "0", this will return the port used for receiving data after
     * a port has been determined. Will return 0 if the connection has not been setup.
     *
     * \return receive port
     */
    U16 getRecvPort();

    /**
     * \brief UDP-specific implementation of send that handles zero-length datagrams correctly.
     * \param socketDescriptor: descriptor to send to
     * \param data: data pointer to send
     * \param size: size of data to send
     * \return: status of the send operation
     */
    SocketIpStatus send(const SocketDescriptor& socketDescriptor, const U8* const data, const U32 size) override;

  protected:
    /**
     * \brief bind the UDP to a port such that it can receive packets at the previously configured port
     * \param socketDescriptor: socket descriptor used in bind
     * \return status of the bind
     */
    SocketIpStatus bind(const int fd);
    /**
     * \brief udp specific implementation for opening a socket.
     * \param socketDescriptor: (output) file descriptor opened. Only valid on SOCK_SUCCESS. Otherwise will be invalid
     * \return status of open
     */
    SocketIpStatus openProtocol(SocketDescriptor& socketDescriptor) override;
    /**
     * \brief Protocol specific implementation of send.  Called directly with retry from send.
     * \param socketDescriptor: descriptor to send to
     * \param data: data to send
     * \param size: size of data to send
     * \return: size of data sent, or -1 on error.
     */
    I32 sendProtocol(const SocketDescriptor& socketDescriptor, const U8* const data, const U32 size) override;
    /**
     * \brief Protocol specific implementation of recv.  Called directly with error handling from recv.
     * \param socketDescriptor: descriptor to recv from
     * \param data: data pointer to fill
     * \param size: size of data buffer
     * \return: size of data received, or -1 on error.
     */
    I32 recvProtocol(const SocketDescriptor& socketDescriptor, U8* const data, const U32 size) override;
    /**
     * \brief Handle zero return from recvProtocol for UDP
     *
     * For UDP, a return of 0 from recvfrom means a 0-byte datagram was received,
     * which is a success case, not a disconnection.
     *
     * @return SocketIpStatus Status to return from recv
     */
    SocketIpStatus handleZeroReturn() override;

  private:
    struct sockaddr_in m_addr_send;  //!< UDP server address for sending
    struct sockaddr_in m_addr_recv;  //!< UDP server address for receiving
    bool m_recv_configured; //!< True if configureRecv was called
};
}  // namespace Drv

#endif /* DRV_IP_UDPSOCKET_HPP_ */
