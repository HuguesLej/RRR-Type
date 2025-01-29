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
    Registry registry;
    ControlSystem controlSystem(registry);
    DrawSystem drawSystem(registry);
    PositionSystem positionSystem(registry);

    registry.registerComponent<Position>();
    registry.registerComponent<Velocity>();
    registry.registerComponent<Drawable>();
    registry.registerComponent<Controllable>();

    Entity e1 = registry.spawnEntity();
    Entity e2 = registry.spawnEntity();

    Position p1 = {0, 0};
    registry.addComponent(e1, &p1);
    registry.addComponent(e1, Velocity{1, 1});
    registry.addComponent(e1, Drawable{});
    registry.addComponent(e1, Controllable{});

    registry.addComponent(e2, Position{10, 10});
    registry.addComponent(e2, Velocity{2, 2});

    for (int i = 0; i < 3; i++) {
        controlSystem.update(1.0f);
        positionSystem.update(1.0f);
        drawSystem.update(1.0f);
    }

    auto &positions = registry.getComponents<Position>();
    auto &velocities = registry.getComponents<Velocity>();

    std::cout << "Entity 1: " << positions[e1]->x << ", " << positions[e1]->y << std::endl;
    std::cout << "Entity 2: " << positions[e2]->x << ", " << positions[e2]->y << std::endl;

    return 0;
}
