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
#include "SFMLGraphical.hpp"

int main(void)
{
    SFMLGraphical graphical(std::string("RRR-Type"));

    while (graphical.isWindowOpen()) {
        graphical.beginFrame();
        graphical.endFrame();
    }
    graphical.closeWindow();

    // RegistryManager registryManager;

    // try {
    //     registryManager.addSystem(std::make_unique<PositionSystem>());
    //     registryManager.addSystem(std::make_unique<DrawSystem>());
    //     registryManager.addSystem(std::make_unique<ControlSystem>());
    // } catch (std::exception const &e) {
    //     std::cerr << e.what() << std::endl;
    //     return 84;
    // }

    // try {
    //     registryManager.registerComponent<comp::Position>();
    //     registryManager.registerComponent<comp::Velocity>();
    //     registryManager.registerComponent<comp::Drawable>();
    //     registryManager.registerComponent<comp::Controllable>();
    // } catch (std::exception const &e) {
    //     std::cerr << e.what() << std::endl;
    //     return 84;
    // }

    // Entity e1 = registryManager.spawnEntity();
    // Entity e2 = registryManager.spawnEntity();

    // try {
    //     registryManager.addComponent(e1, comp::Position{0, 0});
    //     registryManager.addComponent(e1, comp::Velocity{1, 1});
    //     registryManager.addComponent(e1, comp::Drawable{});
    //     registryManager.addComponent(e1, comp::Controllable{});

    //     registryManager.addComponent(e2, comp::Position{10, 10});
    //     registryManager.addComponent(e2, comp::Velocity{2, 2});
    // } catch (std::exception const &e) {
    //     std::cerr << e.what() << std::endl;
    //     return 84;
    // }

    // for (int i = 0; i < 3; i++) {
    //     registryManager.updateSystems(1.0f);
    // }

    // try {
    //     auto &positions = registryManager.getComponents<comp::Position>();
    //     auto &velocities = registryManager.getComponents<comp::Velocity>();

    //     std::cout << "Entity 1: " << positions[e1]->x << ", " << positions[e1]->y << std::endl;
    //     std::cout << "Entity 2: " << positions[e2]->x << ", " << positions[e2]->y << std::endl;
    // } catch (std::exception const &e) {
    //     std::cerr << e.what() << std::endl;
    //     return 84;
    // }

    return 0;
}
