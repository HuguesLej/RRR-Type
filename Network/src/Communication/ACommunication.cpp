/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** ACommunication
*/

#include "ACommunication.hpp"

ACommunication::ACommunication(asio::io_context &io, std::string ip, uint16_t port)
    : _socket(io), _endpoint(asio::ip::make_address(ip), port), _recvStrand(asio::make_strand(io)), _sendStrand(asio::make_strand(io))
{
}

std::optional<std::any> ACommunication::getRecvData()
{
    if (_recvPackets.empty()) {
        return std::nullopt;
    }

    auto data = _recvPackets.front();
    _recvPackets.erase(_recvPackets.begin());
    return SerializerManager::deserialize(data);
}
