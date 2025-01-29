/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
    #define POSITIONSYSTEM_HPP_

    #include "ASystem.hpp"

class PositionSystem : public ASystem
{
    public:
        PositionSystem(std::shared_ptr<Registry> &registry) : ASystem(registry)
        {
        }
        ~PositionSystem() = default;

        void update(float deltaTime) override
        {
            auto &positions = _registry->getComponents<comp::Position>();
            auto &velocities = _registry->getComponents<comp::Velocity>();

            for (std::size_t i = 0; i < positions.size(); i++) {
                if (positions[i] && velocities[i]) {
                    positions[i]->x += velocities[i]->x * deltaTime;
                    positions[i]->y += velocities[i]->y * deltaTime;
                }
            }
        }
};

#endif /* !POSITIONSYSTEM_HPP_ */
