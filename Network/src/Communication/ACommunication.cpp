/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** ACommunication
*/

#include "ACommunication.hpp"

std::optional<std::any> ACommunication::getRecvData()
{
    if (_recvPackets.empty()) {
        return std::nullopt;
    }

    auto data = _recvPackets.front();
    _recvPackets.erase(_recvPackets.begin());
    return SerializerManager::deserialize(data);
}
