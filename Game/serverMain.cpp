/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** serverMain
*/

#include "UDPServerCommunication.hpp"
#include "RegistryManager.hpp"
#include "ControlSystem.hpp"
#include "DrawSystem.hpp"
#include "PositionSystem.hpp"
#include "CollisionSystem.hpp"
#include "GravitySystem.hpp"
#include "JumpSystem.hpp"
#include "HealthSystem.hpp"
#include "NetworkSystem.hpp"
#include "SFMLGraphical.hpp"
#include "Timer.hpp"

void registerSystemsAndComponents(RegistryManager &registryManager)
{
    registryManager.addSystem(std::make_unique<CollisionSystem>());
    registryManager.addSystem(std::make_unique<GravitySystem>());
    registryManager.addSystem(std::make_unique<HealthSystem>());
    registryManager.addSystem(std::make_unique<JumpSystem>());
    registryManager.addSystem(std::make_unique<NetworkSystem>());
    registryManager.addSystem(std::make_unique<PositionSystem>());

    registryManager.registerComponent<comp::Animable>(true);
    registryManager.registerComponent<comp::Collider>();
    registryManager.registerComponent<comp::Controllable>(true);
    registryManager.registerComponent<comp::Drawable>(true);
    registryManager.registerComponent<comp::Gravity>();
    registryManager.registerComponent<comp::Health>();
    registryManager.registerComponent<comp::Jumpable>();
    registryManager.registerComponent<comp::Position>();
    registryManager.registerComponent<comp::Velocity>();
}

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./rrr-type_server <ip> <port>" << std::endl;
        return 84;
    }

    asio::io_context io;
    std::shared_ptr<UDPServerCommunication> server = std::make_shared<UDPServerCommunication>(io, av[1], std::stoi(av[2]));
    RegistryManager registryManager(server);

    try {
        registerSystemsAndComponents(registryManager);
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    Timer timer;

    for (size_t i = 0; i < 10; i++) {
        Entity block = registryManager.spawnEntity();

        try {
            registryManager.addComponent(block, comp::Position{0 + i * 45, 0});
            registryManager.addComponent(block, comp::Drawable{1});
            registryManager.addComponent(block, comp::Collider{45, 14, 1, {}});
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
            return 84;
        }
    }

    Entity enemy = registryManager.spawnEntity();

    try {
        registryManager.addComponent(enemy, comp::Position{200, -50});
        registryManager.addComponent(enemy, comp::Velocity{0, 0});
        registryManager.addComponent(enemy, comp::Drawable{2});
        registryManager.addComponent(enemy, comp::Animable{9, 120});
        registryManager.addComponent(enemy, comp::Collider{30, 26, 1, {1}, 1});
        registryManager.addComponent(enemy, comp::Gravity{1});
        registryManager.addComponent(enemy, comp::Health{1});
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    timer.start();

    while (true) {
        auto elapsedTimeMs = timer.getElapsedTimeMs();

        if (elapsedTimeMs >= 10) {
            timer.reset();

            try {
                registryManager.updateSystems(elapsedTimeMs);
            } catch (std::exception const &e) {
                std::cerr << e.what() << std::endl;
                return 84;
            }
        }
    }

    return 0;
}
