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

class PositionSystem : public ASystem
{
    public:
        PositionSystem() = default;
        ~PositionSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<IGraphical> &graphical, float elapsedSeconds) override
        {
            auto &positions = manager.getComponents<comp::Position>();
            auto &velocities = manager.getComponents<comp::Velocity>();

            for (std::size_t i = 0; i < positions.size(); i++) {
                if (positions[i] && velocities[i]) {
                    positions[i]->x += velocities[i]->x * elapsedSeconds;
                    positions[i]->y += velocities[i]->y * elapsedSeconds;
                }
            }
        }
};

#endif /* !POSITIONSYSTEM_HPP_ */
