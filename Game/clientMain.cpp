/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** clientMain
*/

#include "UDPClientCommunication.hpp"
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
    registryManager.addSystem(std::make_unique<ControlSystem>());
    registryManager.addSystem(std::make_unique<DrawSystem>());
    registryManager.addSystem(std::make_unique<GravitySystem>());
    registryManager.addSystem(std::make_unique<HealthSystem>());
    registryManager.addSystem(std::make_unique<JumpSystem>());
    registryManager.addSystem(std::make_unique<NetworkSystem>());
    registryManager.addSystem(std::make_unique<PositionSystem>());

    registryManager.registerComponent<comp::Animable>();
    registryManager.registerComponent<comp::Collider>();
    registryManager.registerComponent<comp::Controllable>();
    registryManager.registerComponent<comp::Drawable>();
    registryManager.registerComponent<comp::Gravity>();
    registryManager.registerComponent<comp::Health>();
    registryManager.registerComponent<comp::Jumpable>();
    registryManager.registerComponent<comp::Position>();
    registryManager.registerComponent<comp::Velocity>();
}

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./rrr-type_client <ip> <port>" << std::endl;
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
    std::shared_ptr<UDPClientCommunication> client;
    try {
        client = std::make_shared<UDPClientCommunication>(io, av[1], std::stoi(av[2]));
    } catch (std::exception const &e) {
        std::cerr << e.what() << ": " << av[1] << ", " << av[2] << std::endl;
        return 84;
    }
    std::shared_ptr<SFMLGraphical> graphical = std::make_shared<SFMLGraphical>();
    RegistryManager registryManager(graphical, client);

    try {
        graphical->addTextures({
            "assets/sprites/MainCharacters/MaskDude/Idle.png",
            "assets/sprites/Terrain/Iron/Iron1.png",
            "assets/sprites/Enemies/AngryPig/Idle.png",
            "assets/sprites/Enemies/AngryPig/Idle.png"
        });
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    try {
        registerSystemsAndComponents(registryManager);
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    Timer timer;

    // Entity character = registryManager.spawnEntity();

    // try {
    //     registryManager.addComponent(character, comp::Controllable{Keys::Q, Keys::D, Keys::None, Keys::None, Keys::Space});
    // } catch (std::exception const &e) {
    //     std::cerr << e.what() << std::endl;
    //     return 84;
    // }

    graphical->openWindow("RRR-Type");
    timer.start();

    while (graphical->isWindowOpen()) {

        auto elapsedTimeMs = timer.getElapsedTimeMs();
        graphical->beginFrame();

        if (elapsedTimeMs >= 10) {
            timer.reset();

            try {
                registryManager.updateSystems(elapsedTimeMs);
            } catch (std::exception const &e) {
                std::cerr << e.what() << std::endl;
                return 84;
            }
        }

        graphical->endFrame();
    }

    graphical->closeWindow();

    return 0;
}
