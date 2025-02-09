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

void NetworkSystem::update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs)
{
    (void) graphical;
    (void) elapsedMs;

    if (networkCommunication->isServer()) {
        handleServerUpdate(manager, networkCommunication);
    } else {
        handleClientUpdate(manager, networkCommunication);
    }
}

void NetworkSystem::handleServerUpdate(RegistryManager &manager, std::shared_ptr<ACommunication> &networkCommunication)
{
    auto controllableTypeId = std::type_index(typeid(ComponentsRegistry<comp::Controllable>));

    for (auto &registry : manager.getComponentsRegistries()) {
        if (registry.first == controllableTypeId) {
            continue;
        }

        networkCommunication->setSendData(registry.second);
        handlePacketsReceiving(manager, networkCommunication);
    }
}

void NetworkSystem::handleClientUpdate(RegistryManager &manager, std::shared_ptr<ACommunication> &networkCommunication)
{
    try {

        auto &controllables = manager.getComponents<comp::Controllable>();

        networkCommunication->setSendData(controllables);
        handlePacketsReceiving(manager, networkCommunication);

    } catch (RegistryManager::ComponentError const &e) {

        (void) e;
        throw ASystem::SystemError("NetworkSystem", std::vector<std::string>{"Controllable"});

    }
}

void NetworkSystem::handlePacketsReceiving(RegistryManager &manager, std::shared_ptr<ACommunication> &networkCommunication)
{
    auto data = networkCommunication->getRecvData();

    while (data.has_value()) {
        manager.replaceComponent(data.value());

        data = networkCommunication->getRecvData();
    }
}
