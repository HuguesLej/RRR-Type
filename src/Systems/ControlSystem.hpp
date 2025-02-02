/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** ControlSystem
*/

#ifndef CONTROLSYSTEM_HPP_
    #define CONTROLSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "../RegistryManager.hpp"

class ControlSystem : public ASystem
{
    public:
        ControlSystem() = default;
        ~ControlSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<IGraphical> &graphical, float elapsedSeconds) override
        {
            auto &velocities = manager.getComponents<comp::Velocity>();
            auto &controllables = manager.getComponents<comp::Controllable>();

            for (std::size_t i = 0; i < velocities.size(); i++) {
                if (velocities[i] && controllables[i]) {
                    // Define velocity based on input
                }
            }
        }
};

#endif /* !CONTROLSYSTEM_HPP_ */
