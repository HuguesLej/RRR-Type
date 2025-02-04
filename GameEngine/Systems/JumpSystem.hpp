/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** JumpSystem
*/

#ifndef JUMPSYSTEM_HPP_
    #define JUMPSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "../RegistryManager.hpp"

class JumpSystem : public ASystem
{
    public:
        JumpSystem() = default;
        ~JumpSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, uint64_t elapsedMs) override
        {
            try {

                auto &jumpables = manager.getComponents<comp::Jumpable>();
                auto &velocities = manager.getComponents<comp::Velocity>();
                auto &controllables = manager.getComponents<comp::Controllable>();
                auto &colliders = manager.getComponents<comp::Collider>();

                for (std::size_t i = 0; i < jumpables.size(); i++) {

                    if (!jumpables[i] || velocities.size() <= i || controllables.size() <= i || colliders.size() <= i
                        || !velocities[i] || !controllables[i] || !colliders[i]) {
                        continue;
                    }

                    handleJump(graphical, jumpables[i].value(), velocities[i].value(), controllables[i].value(), colliders[i].value(), elapsedMs);

                }

            } catch (RegistryManager::ComponentError const &e) {
                (void) e;
                throw ASystem::SystemError("JumpSystem", std::vector<std::string>{"Jumpable", "Velocity", "Controllable", "Collider"});
            }
        }

    private:

        void handleJump(std::shared_ptr<AGraphical> &graphical, comp::Jumpable &jmp, comp::Velocity &vel, comp::Controllable const &ctrl,
            comp::Collider const &coll, uint64_t const &elapsedMs)
        {
            if (jmp.elapsedTimeMs == 0) {

                if (coll.collidePosY && graphical->isKeyPressed(ctrl.jump)) {
                    vel.negY = jmp.velocity;
                    jmp.elapsedTimeMs += elapsedMs;

                }
            } else if (jmp.elapsedTimeMs >= jmp.durationMs) {

                vel.negY = 0;
                jmp.elapsedTimeMs = 0;

            } else {

                vel.negY = jmp.velocity;
                jmp.elapsedTimeMs += elapsedMs;

            }
        }
};

#endif /* !JUMPSYSTEM_HPP_ */
