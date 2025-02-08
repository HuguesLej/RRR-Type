/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** ControlSystem
*/

#include "ControlSystem.hpp"

void ControlSystem::update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs)
{
    (void) networkCommunication;
    (void) elapsedMs;

    try {

        auto &velocities = manager.getComponents<comp::Velocity>();
        auto &controllables = manager.getComponents<comp::Controllable>();

        for (std::size_t i = 0; i < velocities.size(); i++) {

            if (!velocities[i] || controllables.size() <= i || !controllables[i]) {
                continue;
            }

            updateVelocity(graphical, controllables[i]->left, velocities[i]->negX, controllables[i]->maxVelocity);
            updateVelocity(graphical, controllables[i]->right, velocities[i]->posX, controllables[i]->maxVelocity);
            updateVelocity(graphical, controllables[i]->up, velocities[i]->negY, controllables[i]->maxVelocity);
            updateVelocity(graphical, controllables[i]->down, velocities[i]->posY, controllables[i]->maxVelocity);

            // Add jump

        }

    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        throw ASystem::SystemError("ControlSystem", std::vector<std::string>{"Velocity", "Controllable"});
    }
}

void ControlSystem::updateVelocity(std::shared_ptr<AGraphical> const &graphical, std::pair<Keys, bool> &key, float &velocity, float const maxVelocity)
{
    if (key.first == Keys::None || key.first == Keys::Unknown) {
        return;
    }

    if (graphical->isKeyPressed(key.first)) {
        key.second = true;
        velocity = maxVelocity;
    } else {
        key.second = false;
        velocity = 0;
    }
}
