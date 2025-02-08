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
    asio::io_context io;
    std::shared_ptr<UDPServerCommunication> server = std::make_shared<UDPServerCommunication>(io, "192.168.1.17", 12345);
    RegistryManager registryManager(server);

    try {
        registerSystemsAndComponents(registryManager);
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    Timer timer;

    Entity character = registryManager.spawnEntity();
    Entity block1 = registryManager.spawnEntity();
    Entity block2 = registryManager.spawnEntity();
    Entity enemy = registryManager.spawnEntity();

    try {
        registryManager.addComponent(character, comp::Position{180, 150});
        registryManager.addComponent(character, comp::Velocity{0, 0});
        registryManager.addComponent(character, comp::Drawable{0});
        registryManager.addComponent(character, comp::Animable{11, 100});
        registryManager.addComponent(character, comp::Controllable{Keys::Q, Keys::D, Keys::Z, Keys::S, Keys::Space, 1}); // Maybe move maxVelocity to Velocity component
        registryManager.addComponent(character, comp::Collider{32, 32, 1, {1}});
        registryManager.addComponent(character, comp::Gravity{1});
        registryManager.addComponent(character, comp::Jumpable{2, 300});
        registryManager.addComponent(character, comp::Health{1});

        registryManager.addComponent(block1, comp::Position{200, 200});
        registryManager.addComponent(block1, comp::Drawable{1});
        registryManager.addComponent(block1, comp::Collider{45, 14, 1, {1}});

        registryManager.addComponent(block2, comp::Position{245, 200});
        registryManager.addComponent(block2, comp::Drawable{1});
        registryManager.addComponent(block2, comp::Collider{45, 14, 1, {1}});

        registryManager.addComponent(enemy, comp::Position{265, 150});
        registryManager.addComponent(enemy, comp::Velocity{0, 0});
        registryManager.addComponent(enemy, comp::Drawable{2});
        registryManager.addComponent(enemy, comp::Animable{9, 120});
        registryManager.addComponent(enemy, comp::Collider{30, 30, 1, {1}, 1});
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
