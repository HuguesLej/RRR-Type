/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** GravitySystem
*/

#ifndef GRAVITYSYSTEM_HPP_
    #define GRAVITYSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "../RegistryManager.hpp"

class GravitySystem : public ASystem
{
    public:
        GravitySystem() = default;
        ~GravitySystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, uint64_t elapsedMs) override
        {
            (void) elapsedMs;
            (void) graphical;

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
};

#endif /* !GRAVITYSYSTEM_HPP_ */
