/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** JumpSystem
*/

#ifndef JUMPSYSTEM_HPP_
    #define JUMPSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "RegistryManager.hpp"

class JumpSystem : public ASystem
{
    public:
        JumpSystem() = default;
        ~JumpSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs) override;

    private:
        void handleJump(std::shared_ptr<AGraphical> &graphical, comp::Jumpable &jmp, comp::Velocity &vel, comp::Controllable const &ctrl,
            comp::Collider const &coll, uint64_t const &elapsedMs);
};

#endif /* !JUMPSYSTEM_HPP_ */
