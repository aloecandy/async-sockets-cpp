#ifndef FDR_TCPSOCKET_H
#define FDR_TCPSOCKET_H

#include <DllHelper.h>

#include <basesocket.h>
#include <string>
#include <functional>
#include <thread>

constexpr uint16_t BUFFER_SIZE = 0xFFFF;

class EASYSOCKET_API TCPSocket : public BaseSocket
{
public:
    // Event Listeners:
    std::function<void(std::string)> onMessageReceived = [](std::string msg) { FDR_UNUSED(msg) };
    std::function<void()> onSocketClosed = [](){};

    TCPSocket(FDR_ON_ERROR, int socketId = -1);

    int Send(std::string message);
    int Send(const char *bytes, size_t byteslength);

    void Connect(std::string ipv4, uint16_t port, std::function<void()> onConnected = [](){}, FDR_ON_ERROR);
    void Connect(uint32_t IPv4, uint16_t port, std::function<void()> onConnected = [](){}, FDR_ON_ERROR);

    void Listen();

    void setAddressStruct(sockaddr_in addr);

private:
    static void Receive(TCPSocket *socket);
};

#endif
