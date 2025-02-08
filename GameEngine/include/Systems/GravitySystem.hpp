/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** GravitySystem
*/

#ifndef GRAVITYSYSTEM_HPP_
    #define GRAVITYSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "RegistryManager.hpp"

class GravitySystem : public ASystem
{
    public:
        GravitySystem() = default;
        ~GravitySystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs) override;
};

#endif /* !GRAVITYSYSTEM_HPP_ */
