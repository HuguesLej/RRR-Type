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
#include "Graphicals/SFMLGraphical.hpp"

int main(void)
{
    std::shared_ptr<SFMLGraphical> graphical = std::make_shared<SFMLGraphical>();
    RegistryManager registryManager(graphical);

    try {
        graphical->addTextures({
            "assets/sprites/MainCharacters/MaskDude/Idle.png",
            "assets/sprites/Terrain/Iron/Iron1.png"
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
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    Entity character = registryManager.spawnEntity();
    Entity block = registryManager.spawnEntity();

    try {
        registryManager.addComponent(character, comp::Position{200, 150});
        registryManager.addComponent(character, comp::Velocity{0, 0});
        registryManager.addComponent(character, comp::Drawable{0});
        registryManager.addComponent(character, comp::Animable{11});
        registryManager.addComponent(character, comp::Controllable{Keys::Q, Keys::D, Keys::Z, Keys::S, Keys::Space, 1});
        registryManager.addComponent(character, comp::Collider{32, 32, 1, {1}});
        registryManager.addComponent(character, comp::Gravity{1});

        registryManager.addComponent(block, comp::Position{200, 200});
        registryManager.addComponent(block, comp::Drawable{1});
        registryManager.addComponent(block, comp::Collider{45, 14, 1, {1}});
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    graphical->openWindow("RRR-Type");
    while (graphical->isWindowOpen()) {
        graphical->beginFrame();
        registryManager.updateSystems(1.0f);
        graphical->endFrame();
    }
    graphical->closeWindow();

    return 0;
}
