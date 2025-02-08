/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** UDPServerCommunication
*/

#include "UDPServerCommunication.hpp"

UDPServerCommunication::UDPServerCommunication(asio::io_context &io, std::string ip, uint16_t port)
    : ACommunication(io), _socket(io, asio::ip::udp::endpoint(asio::ip::make_address(ip), port))
{
    std::cerr << "Server is running on " << ip << ":" << std::to_string(port) << std::endl;

    _recvBuff.resize(4096);

    startReceive();
    startSend();

    size_t maxThreads = std::thread::hardware_concurrency();

    if (maxThreads > 4) {
        maxThreads = 4;
    }

    for (size_t i = 0; i < maxThreads; i++) {
        _workers.push_back(std::thread([&io]() {
            io.run();
        }));
    }
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
    // std::cerr << "Received data from " << _endpoint.address().to_string() << ":" << std::to_string(_endpoint.port()) << std::endl;
    if (!error) {
        _recvPackets.push_back(std::vector<uint8_t>(_recvBuff.begin(), _recvBuff.end()));
        _recvBuff.clear();

        _clients.insert(_endpoint);

        startReceive();
    }
}

void UDPServerCommunication::startSend()
{
    _timer.expires_after(std::chrono::milliseconds(1));
    _timer.async_wait(asio::bind_executor(
        _sendStrand,
        std::bind(&UDPServerCommunication::sendData, this)
    ));
}

void UDPServerCommunication::sendData()
{
    if (_sendPackets.empty() || _clients.empty()) {
        // std::cerr << "No data to send" << std::endl;
        startSend();
    } else {
        _sendBuff.clear();
        _sendBuff = std::string(_sendPackets[0].begin(), _sendPackets[0].end());
        _sendPackets.erase(_sendPackets.begin());

        // std::cerr << "Sending data to " << _clients.size() << " clients" << std::endl;
        std::shared_ptr<std::atomic<size_t>> clientsCount = std::make_shared<std::atomic<size_t>>(_clients.size());

        for (const auto &client : _clients) {
            // std::cerr << "Sending data to " << _endpoint.address().to_string() << ":" << std::to_string(_endpoint.port()) << std::endl;
            _socket.async_send_to(
                asio::buffer(_sendBuff),
                client,
                asio::bind_executor(
                    _sendStrand,
                    std::bind(&UDPServerCommunication::handleSend, this, asio::placeholders::error, asio::placeholders::bytes_transferred, clientsCount)
                )
            );
        }
    }
}

void UDPServerCommunication::handleSend(const std::error_code &error, std::size_t, std::shared_ptr<std::atomic<size_t>> clientsCount)
{
    if (!error) {
        // std::cerr << "Sent" << std::endl;
        if (clientsCount->load() <= 1) {
            startSend();
        } else {
            clientsCount->fetch_sub(1);
        }
    } else {
        std::cerr << "Error while sending data: " << error.message() << std::endl;
    }
}
