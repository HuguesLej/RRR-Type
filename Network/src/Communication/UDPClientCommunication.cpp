/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** UDPClientCommunication
*/

#include "UDPClientCommunication.hpp"

UDPClientCommunication::UDPClientCommunication(asio::io_context &io, std::string ip, uint16_t port)
    : ACommunication(io), _socket(io), _endpoint(asio::ip::make_address(ip), port)
{
    _socket.open(asio::ip::udp::v4());

    _recvBuff.resize(1024);

    startReceive();
    startSend();

    size_t maxThreads = std::thread::hardware_concurrency();

    if (maxThreads > 2) {
        maxThreads = 2;
    }

    for (size_t i = 0; i < maxThreads; i++) {
        _workers.push_back(std::thread([&io]() {
            io.run();
        }));
    }
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
    std::cerr << "Received data from " << _endpoint.address().to_string() << ":" << std::to_string(_endpoint.port()) << std::endl;
    if (!error) {
        _recvPackets.push_back(_recvBuff);

        startReceive();
    }
}

void UDPClientCommunication::startSend()
{
    _timer.expires_after(std::chrono::milliseconds(1));
    _timer.async_wait(asio::bind_executor(
        _sendStrand,
        std::bind(&UDPClientCommunication::sendData, this)
    ));
}

void UDPClientCommunication::sendData()
{
    if (_sendBuff.empty()) {
        startSend();
    } else {
        auto sendData = std::string(_sendBuff.begin(), _sendBuff.end());
        _sendBuff.clear();

        std::cerr << "Sending data to " << _endpoint.address().to_string() << ":" << std::to_string(_endpoint.port()) << std::endl;
        _socket.async_send_to(
            asio::buffer(sendData),
            _endpoint,
            asio::bind_executor(
                _sendStrand,
                std::bind(&UDPClientCommunication::handleSend, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
            )
        );
    }
}

void UDPClientCommunication::handleSend(const std::error_code &error, std::size_t)
{
    if (!error) {
        std::cerr << "Sent successfully" << std::endl;
        startSend();
    } else {
        std::cerr << "Error while sending data: " << error.message() << std::endl;
    }
}
