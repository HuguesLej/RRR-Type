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
    try {

        auto &controllables = manager.getComponents<comp::Controllable>();

        networkCommunication->startSend(controllables);
        handlePacketsReceiving(manager, networkCommunication);

    } catch (RegistryManager::ComponentError const &e) {

        (void) e;
        throw ASystem::SystemError("NetworkSystem", std::vector<std::string>{"Controllable"});

    }
}

void NetworkSystem::handleClientUpdate(RegistryManager &manager, std::shared_ptr<ACommunication> &networkCommunication)
{
    auto controllableTypeId = std::type_index(typeid(comp::Controllable));

    for (auto &registry : manager.getComponentsRegistries()) {
        if (registry.first == controllableTypeId) {
            continue;
        }

        networkCommunication->startSend(registry.second);
        handlePacketsReceiving(manager, networkCommunication);
    }
}

void NetworkSystem::handlePacketsReceiving(RegistryManager &manager, std::shared_ptr<ACommunication> &networkCommunication)
{
    auto data = networkCommunication->getRecvData();

    while (data.has_value()) {
        auto registry = std::any_cast<ComponentsRegistry<std::any> &>(data.value());

        manager.replaceComponent(registry);
    }
}
