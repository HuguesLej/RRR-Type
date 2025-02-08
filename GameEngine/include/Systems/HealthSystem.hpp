/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** HealthSystem
*/

#ifndef HEALTHSYSTEM_HPP_
    #define HEALTHSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "RegistryManager.hpp"

class HealthSystem : public ASystem
{
    public:
        HealthSystem() = default;
        ~HealthSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs) override;
};

#endif /* !HEALTHSYSTEM_HPP_ */
