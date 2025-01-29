/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** ControlSystem
*/

#ifndef CONTROLSYSTEM_HPP_
    #define CONTROLSYSTEM_HPP_

    #include "ASystem.hpp"

class ControlSystem : public ASystem
{
    public:
        ControlSystem(std::shared_ptr<Registry> &registry) : ASystem(registry)
        {
        }
        ~ControlSystem() = default;

        void update(float deltaTime) override
        {
            auto &velocities = _registry->getComponents<comp::Velocity>();
            auto &controllables = _registry->getComponents<comp::Controllable>();

            for (std::size_t i = 0; i < velocities.size(); i++) {
                if (velocities[i] && controllables[i]) {
                    // Define velocity based on input
                }
            }
        }
};

#endif /* !CONTROLSYSTEM_HPP_ */
