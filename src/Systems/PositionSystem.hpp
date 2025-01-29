/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
    #define POSITIONSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "../Registry.hpp"

class PositionSystem : public ASystem
{
    public:
        PositionSystem() = default;
        ~PositionSystem() = default;

        void update(Registry &registry, float deltaTime) override
        {
            auto &positions = registry.getComponents<comp::Position>();
            auto &velocities = registry.getComponents<comp::Velocity>();

            for (std::size_t i = 0; i < positions.size(); i++) {
                if (positions[i] && velocities[i]) {
                    positions[i]->x += velocities[i]->x * deltaTime;
                    positions[i]->y += velocities[i]->y * deltaTime;
                }
            }
        }
};

#endif /* !POSITIONSYSTEM_HPP_ */
