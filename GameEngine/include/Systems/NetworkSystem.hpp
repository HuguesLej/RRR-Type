/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** NetworkSystem
*/

#ifndef NETWORKSYSTEM_HPP_
    #define NETWORKSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "ComponentsSerializer.hpp"
    #include "RegistryManager.hpp"

class NetworkSystem : public ASystem
{
    public:
        NetworkSystem();
        ~NetworkSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs) override;

    private:
        void handleServerUpdate(RegistryManager &manager, std::shared_ptr<ACommunication> &networkCommunication);
        void handleClientUpdate(RegistryManager &manager, std::shared_ptr<ACommunication> &networkCommunication);

        void handlePacketsReceiving(RegistryManager &manager, std::shared_ptr<ACommunication> &networkCommunication);
};

#endif /* !NETWORKSYSTEM_HPP_ */
