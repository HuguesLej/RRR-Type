/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** main
*/

#include <iostream>
#include "Systems/ControlSystem.hpp"
#include "Systems/DrawSystem.hpp"
#include "Systems/PositionSystem.hpp"
#include "Systems/CollisionSystem.hpp"
#include "Systems/GravitySystem.hpp"
#include "Systems/JumpSystem.hpp"
#include "Systems/HealthSystem.hpp"
#include "Graphicals/SFMLGraphical.hpp"

int main(void)
{
    std::shared_ptr<SFMLGraphical> graphical = std::make_shared<SFMLGraphical>();
    RegistryManager registryManager(graphical);

    try {
        graphical->addTextures({
            "assets/sprites/MainCharacters/MaskDude/Idle.png",
            "assets/sprites/Terrain/Iron/Iron1.png",
            "assets/sprites/Enemies/AngryPig/Idle.png",
        });
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    try {
        registryManager.addSystem(std::make_unique<PositionSystem>());
        registryManager.addSystem(std::make_unique<DrawSystem>());
        registryManager.addSystem(std::make_unique<ControlSystem>());
        registryManager.addSystem(std::make_unique<CollisionSystem>());
        registryManager.addSystem(std::make_unique<GravitySystem>());
        registryManager.addSystem(std::make_unique<JumpSystem>());
        registryManager.addSystem(std::make_unique<HealthSystem>());
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    try {
        registryManager.registerComponent<comp::Position>();
        registryManager.registerComponent<comp::Velocity>();
        registryManager.registerComponent<comp::Drawable>();
        registryManager.registerComponent<comp::Animable>();
        registryManager.registerComponent<comp::Controllable>();
        registryManager.registerComponent<comp::Collider>();
        registryManager.registerComponent<comp::Gravity>();
        registryManager.registerComponent<comp::Jumpable>();
        registryManager.registerComponent<comp::Health>();
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    Entity character = registryManager.spawnEntity();
    Entity block1 = registryManager.spawnEntity();
    Entity block2 = registryManager.spawnEntity();
    Entity enemy = registryManager.spawnEntity();

    try {
        registryManager.addComponent(character, comp::Position{180, 150});
        registryManager.addComponent(character, comp::Velocity{0, 0});
        registryManager.addComponent(character, comp::Drawable{0});
        registryManager.addComponent(character, comp::Animable{11});
        registryManager.addComponent(character, comp::Controllable{Keys::Q, Keys::D, Keys::Z, Keys::S, Keys::Space, 1}); // Maybe move maxVelocity to Velocity component
        registryManager.addComponent(character, comp::Collider{32, 32, 1, {1}});
        registryManager.addComponent(character, comp::Gravity{1});
        registryManager.addComponent(character, comp::Jumpable{2, 10});
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
        registryManager.addComponent(enemy, comp::Animable{9});
        registryManager.addComponent(enemy, comp::Collider{30, 30, 1, {1}, 1});
        registryManager.addComponent(enemy, comp::Gravity{1});
        registryManager.addComponent(enemy, comp::Health{1});
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    graphical->openWindow("RRR-Type");
    while (graphical->isWindowOpen()) {
        graphical->beginFrame();
        try {
            registryManager.updateSystems(1.0f);
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
            return 84;
        }
        graphical->endFrame();
    }
    graphical->closeWindow();

    return 0;
}
