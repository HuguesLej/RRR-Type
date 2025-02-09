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
    auto animableTypeId = std::type_index(typeid(ComponentsRegistry<comp::Animable>));
    auto drawableTypeId = std::type_index(typeid(ComponentsRegistry<comp::Drawable>));

    bool hasNewClients = false;
    auto &clients = networkCommunication->getClients();

    for (auto &client : clients) {
        if (client.second) {
            createNewPlayer(manager, client.first.address().to_string(), client.first.port());
            client.second = false;
            hasNewClients = true;
        }
    }

    for (auto &registry : manager.getComponentsRegistries()) {

        if (registry.first == controllableTypeId) {
            auto &controllables = manager.getComponents<comp::Controllable>();
            if (controllables.sendOnce()) {
                if (hasNewClients) {
                    controllables.sent(false);
                }
                if (controllables.sent()) {
                    continue;
                }
                controllables.sent(true);
            }
        }

        if (registry.first == animableTypeId) {
            auto &animables = manager.getComponents<comp::Animable>();
            if (animables.sendOnce()) {
                if (hasNewClients) {
                    animables.sent(false);
                }
                if (animables.sent()) {
                    continue;
                }
                animables.sent(true);
            }
        }

        if (registry.first == drawableTypeId) {
            auto &drawables = manager.getComponents<comp::Drawable>();
            if (drawables.sendOnce()) {
                if (hasNewClients) {
                    drawables.sent(false);
                }
                if (drawables.sent()) {
                    continue;
                }
                drawables.sent(true);
            }
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

void NetworkSystem::createNewPlayer(RegistryManager &manager, const std::string ip, const uint16_t port)
{
    Entity character = manager.spawnEntity();

    manager.addComponent(character, comp::Controllable{Keys::Q, Keys::D, Keys::None, Keys::None, Keys::Space, ip, port});
    manager.addComponent(character, comp::Position{50, -50});
    manager.addComponent(character, comp::Velocity{1, 0});
    manager.addComponent(character, comp::Drawable{0});
    manager.addComponent(character, comp::Animable{11, 100});
    manager.addComponent(character, comp::Collider{32, 32, 1, {1}});
    manager.addComponent(character, comp::Gravity{1});
    manager.addComponent(character, comp::Jumpable{2, 300});
    manager.addComponent(character, comp::Health{1});
}
