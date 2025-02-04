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

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, uint64_t elapsedMs) override;

    private:
        void updateVelocity(std::shared_ptr<AGraphical> &graphical, Keys key, float &velocity, float maxVelocity);
};

#endif /* !CONTROLSYSTEM_HPP_ */
