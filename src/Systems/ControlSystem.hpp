/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** ControlSystem
*/

#ifndef CONTROLSYSTEM_HPP_
    #define CONTROLSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "../Registry.hpp"

class ControlSystem : public ASystem
{
    public:
        ControlSystem() = default;
        ~ControlSystem() = default;

        void update(Registry &registry, float deltaTime) override
        {
            auto &velocities = registry.getComponents<comp::Velocity>();
            auto &controllables = registry.getComponents<comp::Controllable>();

            for (std::size_t i = 0; i < velocities.size(); i++) {
                if (velocities[i] && controllables[i]) {
                    // Define velocity based on input
                }
            }
        }
};

#endif /* !CONTROLSYSTEM_HPP_ */
