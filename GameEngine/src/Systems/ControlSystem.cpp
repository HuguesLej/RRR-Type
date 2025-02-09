/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** ControlSystem
*/

#include "ControlSystem.hpp"

void ControlSystem::update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs)
{
    (void) elapsedMs;

    try {

        auto &controllables = manager.getComponents<comp::Controllable>();

        for (std::size_t i = 0; i < controllables->size(); i++) {

            if (!controllables[i]) {
                continue;
            }

            if (networkCommunication && !networkCommunication->isServer()) {

                auto local = networkCommunication->getLocalAddressAndPort();

                if (local.first == controllables[i]->localAddress && local.second == controllables[i]->localPort) {
                    updateKeyState(graphical, controllables[i]->left);
                    updateKeyState(graphical, controllables[i]->right);
                    updateKeyState(graphical, controllables[i]->up);
                    updateKeyState(graphical, controllables[i]->down);
                    updateKeyState(graphical, controllables[i]->jump);
                } else {
                    controllables[i] = std::nullopt;
                }

                continue;

            }

            updateKeyState(graphical, controllables[i]->left);
            updateKeyState(graphical, controllables[i]->right);
            updateKeyState(graphical, controllables[i]->up);
            updateKeyState(graphical, controllables[i]->down);
            updateKeyState(graphical, controllables[i]->jump);

        }

    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        throw ASystem::SystemError("ControlSystem", std::vector<std::string>{"Velocity", "Controllable"});
    }
}

void ControlSystem::updateKeyState(std::shared_ptr<AGraphical> const &graphical, std::pair<Keys, bool> &key)
{
    if (key.first == Keys::None || key.first == Keys::Unknown) {
        return;
    }

    if (graphical->isKeyPressed(key.first)) {
        key.second = true;
    } else {
        key.second = false;
    }
}
