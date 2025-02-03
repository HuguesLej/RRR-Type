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
#include "Graphicals/SFMLGraphical.hpp"

int main(void)
{
    std::shared_ptr<SFMLGraphical> graphical = std::make_shared<SFMLGraphical>();
    RegistryManager registryManager(graphical);

    try {
        graphical->addTextures({
            "assets/sprites/MainCharacters/MaskDude/Idle.png"
        });
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    try {
        registryManager.addSystem(std::make_unique<PositionSystem>());
        registryManager.addSystem(std::make_unique<DrawSystem>());
        registryManager.addSystem(std::make_unique<ControlSystem>());
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
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    Entity e1 = registryManager.spawnEntity();

    try {
        registryManager.addComponent(e1, comp::Position{0, 0});
        registryManager.addComponent(e1, comp::Velocity{0, 0});
        registryManager.addComponent(e1, comp::Drawable{0});
        registryManager.addComponent(e1, comp::Animable{11});
        registryManager.addComponent(e1, comp::Controllable{Keys::Q, Keys::D, Keys::Z, Keys::S, Keys::Space, 1});
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
