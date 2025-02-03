/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
    #define POSITIONSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "../RegistryManager.hpp"

#include <iostream>
class PositionSystem : public ASystem
{
    public:
        PositionSystem() = default;
        ~PositionSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, float elapsedSeconds) override
        {
            (void) graphical;

            auto &positions = manager.getComponents<comp::Position>();
            auto &velocities = manager.getComponents<comp::Velocity>();

            for (std::size_t i = 0; i < positions.size(); i++) {
                if (positions[i] && velocities[i]) {
                    positions[i]->x += (velocities[i]->negX + velocities[i]->posX) * elapsedSeconds;
                    positions[i]->y += (velocities[i]->negY + velocities[i]->posY) * elapsedSeconds;
                }
            }
        }
};

#endif /* !POSITIONSYSTEM_HPP_ */
