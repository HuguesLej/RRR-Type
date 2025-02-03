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

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, float elapsedSeconds) override
        {
            (void) elapsedSeconds;

            try {

                auto &velocities = manager.getComponents<comp::Velocity>();
                auto &controllables = manager.getComponents<comp::Controllable>();

                for (std::size_t i = 0; i < velocities.size(); i++) {

                    if (!velocities[i] || controllables.size() <= i || !controllables[i]) {
                        continue;
                    }

                    updateVelocity(graphical, controllables[i]->left, velocities[i]->negX, -controllables[i]->maxVelocity);
                    updateVelocity(graphical, controllables[i]->right, velocities[i]->posX, controllables[i]->maxVelocity);
                    updateVelocity(graphical, controllables[i]->up, velocities[i]->negY, -controllables[i]->maxVelocity);
                    updateVelocity(graphical, controllables[i]->down, velocities[i]->posY, controllables[i]->maxVelocity);

                    // Add jump

                }

            } catch (RegistryManager::ComponentError const &e) {
                (void) e;
                throw ASystem::SystemError("ControlSystem", std::vector<std::string>{"Velocity", "Controllable"});
            }
        }

    private:

        void updateVelocity(std::shared_ptr<AGraphical> &graphical, Keys key, float &velocity, float maxVelocity)
        {
            if (key == Keys::Unknown) {
                return;
            }

            if (graphical->isKeyPressed(key)) {
                velocity = maxVelocity;
            } else {
                velocity = 0;
            }
        }
};

#endif /* !CONTROLSYSTEM_HPP_ */
