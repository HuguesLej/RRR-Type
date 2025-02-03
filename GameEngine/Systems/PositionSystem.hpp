/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
    #define POSITIONSYSTEM_HPP_

    #include <algorithm>
    #include "ASystem.hpp"
    #include "../RegistryManager.hpp"

class PositionSystem : public ASystem
{
    public:
        PositionSystem() = default;
        ~PositionSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, float elapsedSeconds) override
        {
            (void) graphical;

            try {

                auto &positions = manager.getComponents<comp::Position>();
                auto &velocities = manager.getComponents<comp::Velocity>();

                try {
                    auto &colliders = manager.getComponents<comp::Collider>();

                    for (std::size_t i = 0; i < positions.size(); i++) {
                        if (positions[i] && velocities[i]) {

                            auto velPosX = velocities[i]->posX;
                            auto velNegX = velocities[i]->negX;
                            auto velPosY = velocities[i]->posY;
                            auto velNegY = velocities[i]->negY;

                            if (colliders[i]) {

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

                            positions[i]->x += (velNegX + velPosX) * elapsedSeconds;
                            positions[i]->y += (velNegY + velPosY) * elapsedSeconds;
                        }
                    }

                } catch (std::exception const &e) {
                    (void) e;

                    for (std::size_t i = 0; i < positions.size(); i++) {
                        if (positions[i] && velocities[i]) {
                            positions[i]->x += (velocities[i]->negX + velocities[i]->posX) * elapsedSeconds;
                            positions[i]->y += (velocities[i]->negY + velocities[i]->posY) * elapsedSeconds;
                        }
                    }
                }

            } catch (RegistryManager::ComponentError const &e) {
                (void) e;
                throw ASystem::SystemError("PositionSystem", std::vector<std::string>{"Position", "Velocity"});
            }
        }
};

#endif /* !POSITIONSYSTEM_HPP_ */
