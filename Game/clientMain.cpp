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
    registryManager.addSystem(std::make_unique<GravitySystem>());
    registryManager.addSystem(std::make_unique<HealthSystem>());
    registryManager.addSystem(std::make_unique<JumpSystem>());
    registryManager.addSystem(std::make_unique<PositionSystem>());
    registryManager.addSystem(std::make_unique<NetworkSystem>());

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

int main(void)
{
    asio::io_context io;
    std::shared_ptr<UDPClientCommunication> client = std::make_shared<UDPClientCommunication>(io, "192.168.1.17", 12345);
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

    Entity character = registryManager.spawnEntity();

    try {
        registryManager.addComponent(character, comp::Controllable{Keys::Q, Keys::D, Keys::Z, Keys::S, Keys::Space, 1}); // Maybe move maxVelocity to Velocity component
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

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
