/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** JumpSystem
*/

#include "JumpSystem.hpp"

void JumpSystem::update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, uint64_t elapsedMs)
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

void JumpSystem::handleJump(std::shared_ptr<AGraphical> &graphical, comp::Jumpable &jmp, comp::Velocity &vel, comp::Controllable const &ctrl,
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
