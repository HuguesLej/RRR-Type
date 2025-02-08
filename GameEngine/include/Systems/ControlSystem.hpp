/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** ControlSystem
*/

#ifndef CONTROLSYSTEM_HPP_
    #define CONTROLSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "RegistryManager.hpp"

class ControlSystem : public ASystem
{
    public:
        ControlSystem() = default;
        ~ControlSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs) override;

    private:
        void updateVelocity(std::shared_ptr<AGraphical> const &graphical, std::pair<Keys, bool> &key, float &velocity, float const maxVelocity);
};

#endif /* !CONTROLSYSTEM_HPP_ */
