/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** HealthSystem
*/

#include "HealthSystem.hpp"

void HealthSystem::update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs)
{
    (void) graphical;
    (void) networkCommunication;
    (void) elapsedMs;

    try {

        auto &healths = manager.getComponents<comp::Health>();
        auto &colliders = manager.getComponents<comp::Collider>();

        for (std::size_t i = 0; i < healths->size(); i++) {

            if (!healths[i] || colliders->size() <= i || !colliders[i]) {
                continue;
            }

            if (healths[i]->health <= colliders[i]->collisionTakenDamage) {
                healths[i] = 0;
                manager.killEntity(i);
            } else {
                healths[i]->health -= colliders[i]->collisionTakenDamage;
            }

        }

    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        throw ASystem::SystemError("HealthSystem", std::vector<std::string>{"Health", "Collider"});
    }
}
