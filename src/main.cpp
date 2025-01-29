/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** main
*/

#include <iostream>
#include "ControlSystem.hpp"
#include "DrawSystem.hpp"
#include "PositionSystem.hpp"

int main(void)
{
    std::shared_ptr<Registry> registry = std::make_shared<Registry>();
    ControlSystem controlSystem(registry);
    DrawSystem drawSystem(registry);
    PositionSystem positionSystem(registry);

    registry->registerComponent<comp::Position>();
    registry->registerComponent<comp::Velocity>();
    registry->registerComponent<comp::Drawable>();
    registry->registerComponent<comp::Controllable>();

    Entity e1 = registry->spawnEntity();
    Entity e2 = registry->spawnEntity();

    registry->addComponent(e1, comp::Position{0, 0});
    registry->addComponent(e1, comp::Velocity{1, 1});
    registry->addComponent(e1, comp::Drawable{});
    registry->addComponent(e1, comp::Controllable{});

    registry->addComponent(e2, comp::Position{10, 10});
    registry->addComponent(e2, comp::Velocity{2, 2});

    for (int i = 0; i < 3; i++) {
        controlSystem.update(1.0f);
        positionSystem.update(1.0f);
        drawSystem.update(1.0f);
    }

    auto &positions = registry->getComponents<comp::Position>();
    auto &velocities = registry->getComponents<comp::Velocity>();

    std::cout << "Entity 1: " << positions[e1]->x << ", " << positions[e1]->y << std::endl;
    std::cout << "Entity 2: " << positions[e2]->x << ", " << positions[e2]->y << std::endl;

    return 0;
}
