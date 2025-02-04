/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** HealthSystem
*/

#ifndef HEALTHSYSTEM_HPP_
    #define HEALTHSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "../RegistryManager.hpp"

class HealthSystem : public ASystem
{
    public:
        HealthSystem() = default;
        ~HealthSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, uint64_t elapsedMs) override
        {
            (void) graphical;
            (void) elapsedMs;

            try {

                auto &healths = manager.getComponents<comp::Health>();
                auto &colliders = manager.getComponents<comp::Collider>();

                for (std::size_t i = 0; i < healths.size(); i++) {

                    if (!healths[i] || colliders.size() <= i || !colliders[i]) {
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
};

#endif /* !HEALTHSYSTEM_HPP_ */
