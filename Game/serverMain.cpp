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

#define DEBUG_INVISIBLE_WALLS

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

    for (auto c : std::string(av[1])) {
        if ((c < '0' || c > '9') && c != '.') {
            std::cerr << "Invalid IP: " << av[1] << std::endl;
            return 84;
        }
    }
    for (auto c : std::string(av[2])) {
        if (c < '0' || c > '9') {
            std::cerr << "Invalid port: " << av[2] << std::endl;
            return 84;
        }
    }

    asio::io_context io;
    std::shared_ptr<UDPServerCommunication> server;
    try {
        server = std::make_shared<UDPServerCommunication>(io, av[1], std::stoi(av[2]));
    } catch (std::exception const &e) {
        std::cerr << e.what() << ": " << av[1] << ", " << av[2] << std::endl;
        return 84;
    }
    RegistryManager registryManager(server);

    try {
        registerSystemsAndComponents(registryManager);
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    Timer timer;

    try {

        Entity background = registryManager.spawnEntity();
        registryManager.addComponent(background, comp::Position{});
        registryManager.addComponent(background, comp::Drawable{4, true});

        for (size_t i = 0; i < 20; i++) {
            if (i >= 10 && i <= 12) {
                Entity invisibleBlock = registryManager.spawnEntity();
                registryManager.addComponent(invisibleBlock, comp::Position{7.0f + (float) i * 45, 100.0f});
                #ifdef DEBUG_INVISIBLE_WALLS
                    registryManager.addComponent(invisibleBlock, comp::Drawable{9});
                #endif
                registryManager.addComponent(invisibleBlock, comp::Collider{14, 45, 1, {}, 1});
            }
        }
    
        Entity block1 = registryManager.spawnEntity();
        registryManager.addComponent(block1, comp::Position{0, 0});
        registryManager.addComponent(block1, comp::Drawable{8});
        registryManager.addComponent(block1, comp::Collider{14, 14, 1, {}});

        for (size_t i = 0; i < 10; i++) {
            Entity block = registryManager.spawnEntity();
            try {
                registryManager.addComponent(block, comp::Position{0, -30.0f - (float) i * 45});
                registryManager.addComponent(block, comp::Drawable{6});
                registryManager.addComponent(block, comp::Collider{14, 45, 1, {}});
            } catch (std::exception const &e) {
                std::cerr << e.what() << std::endl;
                return 84;
            }
        }

        for (size_t i = 0; i < 15; i++) {

            if (i == 10 || i == 11) {
                continue;
            }

            Entity block = registryManager.spawnEntity();
            registryManager.addComponent(block, comp::Position{30.0f + (float) i * 45, 0});
            registryManager.addComponent(block, comp::Drawable{5});
            registryManager.addComponent(block, comp::Collider{45, 14, 1, {}});
        }

        Entity enemy1 = registryManager.spawnEntity();
        registryManager.addComponent(enemy1, comp::Position{400, -50});
        registryManager.addComponent(enemy1, comp::Velocity{0, 0});
        registryManager.addComponent(enemy1, comp::Drawable{13});
        registryManager.addComponent(enemy1, comp::Animable{9, 120});
        registryManager.addComponent(enemy1, comp::Collider{30, 26, 1, {1}, 1});
        registryManager.addComponent(enemy1, comp::Gravity{1});
        registryManager.addComponent(enemy1, comp::Health{1});

        float y = 10.0f;
        for (size_t i = 0; i < 10; i++) {
            if (i % 2 == 0) {
                y -= 50.0f;
            }
            Entity block = registryManager.spawnEntity();
            registryManager.addComponent(block, comp::Position{750.0f + (float) i * 45, y});
            registryManager.addComponent(block, comp::Drawable{5});
            registryManager.addComponent(block, comp::Collider{45, 14, 1, {}});
        }

        Entity enemy2 = registryManager.spawnEntity();
        registryManager.addComponent(enemy2, comp::Position{800, -150});
        registryManager.addComponent(enemy2, comp::Velocity{0, 0});
        registryManager.addComponent(enemy2, comp::Drawable{13});
        registryManager.addComponent(enemy2, comp::Animable{9, 120});
        registryManager.addComponent(enemy2, comp::Collider{30, 26, 1, {1}, 1});
        registryManager.addComponent(enemy2, comp::Gravity{1});
        registryManager.addComponent(enemy2, comp::Health{1});

        Entity enemy3 = registryManager.spawnEntity();
        registryManager.addComponent(enemy3, comp::Position{1020, -250});
        registryManager.addComponent(enemy3, comp::Velocity{0, 0});
        registryManager.addComponent(enemy3, comp::Drawable{13});
        registryManager.addComponent(enemy3, comp::Animable{9, 120});
        registryManager.addComponent(enemy3, comp::Collider{30, 26, 1, {1}, 1});
        registryManager.addComponent(enemy3, comp::Gravity{1});
        registryManager.addComponent(enemy3, comp::Health{1});

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
