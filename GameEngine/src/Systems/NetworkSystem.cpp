/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** NetworkSystem
*/

#include "NetworkSystem.hpp"

NetworkSystem::NetworkSystem()
{
    ComponentsSerializer::registerSerializers();
}

void NetworkSystem::update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, uint64_t elapsedMs)
{
    (void)manager;
    (void)graphical;
    (void)elapsedMs;
}
