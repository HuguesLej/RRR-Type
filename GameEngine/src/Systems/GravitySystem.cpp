/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** GravitySystem
*/

#include "GravitySystem.hpp"

void GravitySystem::update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs)
{
    (void) graphical;
    (void) networkCommunication;
    (void) elapsedMs;

    try {

        auto &gravities = manager.getComponents<comp::Gravity>();
        auto &velocities = manager.getComponents<comp::Velocity>();
        auto &colliders = manager.getComponents<comp::Collider>();

        for (std::size_t i = 0; i < gravities.size(); i++) {

            if (!gravities[i] || velocities.size() <= i || colliders.size() <= i || !velocities[i] || !colliders[i]) {
                continue;
            }

            if (colliders[i]->collidePosY) {
                velocities[i]->posY = 0;
            } else {
                velocities[i]->posY = gravities[i]->velocity;
            }

        }

    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        throw ASystem::SystemError("GravitySystem", std::vector<std::string>{"Gravity", "Velocity", "Controllable"});
    }
}
