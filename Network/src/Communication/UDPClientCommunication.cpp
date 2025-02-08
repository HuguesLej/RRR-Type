/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** UDPClientCommunication
*/

#include "UDPClientCommunication.hpp"

UDPClientCommunication::UDPClientCommunication(asio::io_context &io, std::string ip, uint16_t port)
    : ACommunication(io, ip, port)
{
    _socket.open(asio::ip::udp::v4());

    size_t maxThreads = std::thread::hardware_concurrency();

    if (maxThreads > 4) {
        maxThreads = 4;
    }

    for (size_t i = 0; i < maxThreads; i++) {
        _workers.push_back(std::thread([&io]() {
            io.run();
        }));
    }

    startReceive();
}

UDPClientCommunication::~UDPClientCommunication()
{
    for (auto &worker : _workers) {
        worker.join();
    }
}

bool UDPClientCommunication::isServer()
{
    return false;
}

void UDPClientCommunication::startReceive()
{
    _socket.async_receive_from(
        asio::buffer(_recvBuff),
        _endpoint,
        asio::bind_executor(
            _recvStrand,
            std::bind(&UDPClientCommunication::handleReceive, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
        )
    );
}

void UDPClientCommunication::handleReceive(const std::error_code &error, std::size_t)
{
    if (!error) {
        _recvPackets.push_back(_recvBuff);

        startReceive();
    }
}

void UDPClientCommunication::startSend(const std::any &data)
{
    auto serializedData = SerializerManager::serialize(data);

    _socket.async_send_to(
        asio::buffer(serializedData),
        _endpoint,
        asio::bind_executor(
            _sendStrand,
            std::bind(&UDPClientCommunication::handleSend, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
        )
    );
}

void UDPClientCommunication::handleSend(const std::error_code &error, std::size_t)
{
    if (!error) {
        std::cerr << "Error while sending data: " << error.message() << std::endl;
    }
}
