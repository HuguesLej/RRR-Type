/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** UDPServerCommunication
*/

#include "UDPServerCommunication.hpp"

UDPServerCommunication::UDPServerCommunication(asio::io_context &io, std::string ip, uint16_t port)
    : ACommunication(io, ip, port)
{
    std::cerr << "Server is running on " << ip << ":" << std::to_string(port) << std::endl;

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

UDPServerCommunication::~UDPServerCommunication()
{
    for (auto &worker : _workers) {
        worker.join();
    }
}

bool UDPServerCommunication::isServer()
{
    return true;
}

void UDPServerCommunication::startReceive()
{
    _socket.async_receive_from(
        asio::buffer(_recvBuff),
        _endpoint,
        asio::bind_executor(
            _recvStrand,
            std::bind(&UDPServerCommunication::handleReceive, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
        )
    );
}

void UDPServerCommunication::handleReceive(const std::error_code &error, std::size_t)
{
    if (!error) {
        _recvPackets.push_back(_recvBuff);

        _clients.insert(_endpoint);

        startReceive();
    }
}

void UDPServerCommunication::startSend(const std::any &data)
{
    auto serializedData = SerializerManager::serialize(data);

    for (const auto &client : _clients) {
        _socket.async_send_to(
            asio::buffer(serializedData),
            client,
            asio::bind_executor(
                _sendStrand,
                std::bind(&UDPServerCommunication::handleSend, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
            )
        );
    }
}

void UDPServerCommunication::handleSend(const std::error_code &error, std::size_t)
{
    if (error) {
        std::cerr << "Error while sending data: " << error.message() << std::endl;
    }
}
