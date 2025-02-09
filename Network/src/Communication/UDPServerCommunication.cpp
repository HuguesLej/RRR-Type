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
    _stop = true;

    _io.stop();

    for (auto &worker : _workers) {
        worker.join();
    }
}

bool UDPServerCommunication::isServer()
{
    return true;
}

std::unordered_map<asio::ip::udp::endpoint, bool> &UDPServerCommunication::getClients()
{
    return _clients;
}

std::pair<std::string, uint16_t> UDPServerCommunication::getLocalAddressAndPort()
{
    return std::make_pair(_socket.local_endpoint().address().to_string(), _socket.local_endpoint().port());
}

void UDPServerCommunication::startReceive()
{
    if (_stop) {
        return;
    }

    std::shared_ptr<std::string> data = std::make_shared<std::string>();
    data->resize(4096);

    _socket.async_receive_from(
        asio::buffer(*data),
        _endpoint,
        asio::bind_executor(
            _recvStrand,
            std::bind(&UDPServerCommunication::handleReceive, this, data, asio::placeholders::error, asio::placeholders::bytes_transferred)
        )
    );
}

void UDPServerCommunication::handleReceive(std::shared_ptr<std::string> &data, const std::error_code &error, std::size_t)
{
    if (!error) {

        std::unique_lock<std::mutex> lock(_recvMutex);
        _recvPackets.push_back(std::vector<uint8_t>(data->begin(), data->end()));

        if (_clients.find(_endpoint) == _clients.end()) {
            _clients[_endpoint] = true;
        }
        lock.unlock();

        startReceive();
    }
}

void UDPServerCommunication::startSend()
{
    if (_stop) {
        return;
    }

    _timer.expires_after(std::chrono::milliseconds(1));
    _timer.async_wait(asio::bind_executor(
        _sendStrand,
        std::bind(&UDPServerCommunication::sendData, this)
    ));
}

void UDPServerCommunication::sendData()
{
    if (_stop) {
        return;
    }

    std::unique_lock<std::mutex> lock(_sendMutex);
    if (_sendPackets.empty() || _clients.empty()) {
        _sendPackets.clear();
        lock.unlock();
        startSend();
    } else {
        std::string data = std::string(_sendPackets[0].begin(), _sendPackets[0].end());

        _sendPackets.erase(_sendPackets.begin());
        lock.unlock();

        std::shared_ptr<std::atomic<size_t>> clientsCount = std::make_shared<std::atomic<size_t>>(_clients.size());

        for (const auto &client : _clients) {
            _socket.async_send_to(
                asio::buffer(data),
                client.first,
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
        if (clientsCount->load() <= 1) {
            startSend();
        } else {
            clientsCount->fetch_sub(1);
        }
    } else {
        std::cerr << "Error while sending data: " << error.message() << std::endl;
    }
}
