/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** PositionSystem
*/

#include "PositionSystem.hpp"

void PositionSystem::update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs)
{
    (void) graphical;
    (void) networkCommunication;

    try {

        auto &positions = manager.getComponents<comp::Position>();
        auto &velocities = manager.getComponents<comp::Velocity>();
        auto &colliders = getColliders(manager);
        auto &controllables = getControllables(manager);

        handlePositions(positions, velocities, colliders, controllables, elapsedMs);

    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        throw ASystem::SystemError("PositionSystem", std::vector<std::string>{"Position", "Velocity"});
    }
}

void PositionSystem::handlePositions(ComponentsRegistry<comp::Position> &positions, ComponentsRegistry<comp::Velocity> const &velocities,
    ComponentsRegistry<comp::Collider> const &colliders, ComponentsRegistry<comp::Controllable> const &controllables, uint64_t const &elapsedMs)
{
    for (std::size_t i = 0; i < positions.size(); i++) {

        if (!positions[i] || velocities.size() <= i || !velocities[i]) {
            continue;
        }

        auto velPosX = velocities[i]->posX;
        auto velNegX = velocities[i]->negX;
        auto velPosY = velocities[i]->posY;
        auto velNegY = velocities[i]->negY;

        if (controllables.size() > i && controllables[i]) {

            if (!controllables[i]->right) {
                velPosX = 0;
            }
            if (!controllables[i]->left) {
                velNegX = 0;
            }
            if (!controllables[i]->down) {
                velPosY = 0;
            }
            if (!controllables[i]->up) {
                velNegY = 0;
            }

        }

        if (colliders.size() > i && colliders[i]) {

            if (colliders[i]->collidePosX) {
                velPosX = 0;
            }
            if (colliders[i]->collideNegX) {
                velNegX = 0;
            }
            if (colliders[i]->collidePosY) {
                velPosY = 0;
            }
            if (colliders[i]->collideNegY) {
                velNegY = 0;
            }

        }

        positions[i]->x += (velPosX - velNegX) * elapsedMs / 10;
        positions[i]->y += (velPosY - velNegY) * elapsedMs / 10;

    }
}

ComponentsRegistry<comp::Collider> PositionSystem::getColliders(RegistryManager &manager)
{
    try {
        return manager.getComponents<comp::Collider>();
    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        return ComponentsRegistry<comp::Collider>();
    }
}

ComponentsRegistry<comp::Controllable> PositionSystem::getControllables(RegistryManager &manager)
{
    try {
        return manager.getComponents<comp::Controllable>();
    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        return ComponentsRegistry<comp::Controllable>();
    }
}
