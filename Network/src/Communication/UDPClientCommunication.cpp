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
    _socket.connect(_endpoint);

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
    _stop = true;

    _io.stop();

    for (auto &worker : _workers) {
        worker.join();
    }
}

bool UDPClientCommunication::isServer()
{
    return false;
}

std::vector<std::pair<asio::ip::udp::endpoint, bool>> &UDPClientCommunication::getClients()
{
    throw Error(Error::OriginType::Client);
}

std::pair<std::string, uint16_t> UDPClientCommunication::getLocalAddressAndPort()
{
    return std::make_pair(_socket.local_endpoint().address().to_string(), _socket.local_endpoint().port());
}

void UDPClientCommunication::startReceive()
{
    if (_stop) {
        return;
    }

    std::shared_ptr<std::string> data = std::make_shared<std::string>();
    // data->resize(8192);
    data->resize(4096);

    _socket.async_receive_from(
        asio::buffer(*data),
        _endpoint,
        asio::bind_executor(
            _recvStrand,
            std::bind(&UDPClientCommunication::handleReceive, this, data, asio::placeholders::error, asio::placeholders::bytes_transferred)
        )
    );
}

void UDPClientCommunication::handleReceive(std::shared_ptr<std::string> &data, const std::error_code &error, std::size_t)
{
    if (!error) {

        std::unique_lock<std::mutex> lock(_recvMutex);
        _recvPackets.push_back(std::vector<uint8_t>(data->begin(), data->end()));
        lock.unlock();

        startReceive();
    }
}

void UDPClientCommunication::startSend()
{
    if (_stop) {
        return;
    }

    _timer.expires_after(std::chrono::milliseconds(1));
    _timer.async_wait(asio::bind_executor(
        _sendStrand,
        std::bind(&UDPClientCommunication::sendData, this)
    ));
}

void UDPClientCommunication::sendData()
{
    if (_stop) {
        return;
    }

    std::unique_lock<std::mutex> lock(_sendMutex);
    if (_sendPackets.empty()) {
        lock.unlock();
        startSend();
    } else {
        std::string data = std::string(_sendPackets[0].begin(), _sendPackets[0].end());

        _sendPackets.erase(_sendPackets.begin());
        lock.unlock();

        _socket.async_send_to(
            asio::buffer(data),
            _endpoint,
            asio::bind_executor(
                _sendStrand,
                std::bind(&UDPClientCommunication::handleSend, this, asio::placeholders::error, asio::placeholders::bytes_transferred, nullptr)
            )
        );
    }
}

void UDPClientCommunication::handleSend(const std::error_code &error, std::size_t, std::shared_ptr<std::atomic<size_t>>)
{
    if (!error) {
        startSend();
    } else {
        std::cerr << "Error while sending data: " << error.message() << std::endl;
    }
}
