/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** ACommunication
*/

#include "ACommunication.hpp"

ACommunication::ACommunication(asio::io_context &io) : _recvStrand(asio::make_strand(io)), _sendStrand(asio::make_strand(io)), _timer(io)
{
}

void ACommunication::setSendData(const std::any &data)
{
    try {
        auto packet = SerializerManager::serialize(data);
        std::unique_lock<std::mutex> lock(_sendMutex);
        _sendPackets.push_back(packet);
        lock.unlock();
    } catch (const SerializerManager::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

std::optional<std::any> ACommunication::getRecvData()
{
    std::unique_lock<std::mutex> lock(_recvMutex);
    if (_recvPackets.empty()) {
        lock.unlock();
        return std::nullopt;
    }

    auto data = _recvPackets.front();
    _recvPackets.erase(_recvPackets.begin());
    lock.unlock();

    try {
        return SerializerManager::deserialize(data);
    } catch (const SerializerManager::Error &e) {
        std::cerr << e.what() << std::endl;
        return std::nullopt;
    }
}
