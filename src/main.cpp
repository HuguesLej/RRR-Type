/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** main
*/

#include <iostream>
#include "Registry.hpp"

struct Position
{
    float x;
    float y;
};

struct Velocity
{
    float x;
    float y;
};

struct Drawable
{
};

struct Controllable
{
};

int main(void)
{
    Registry registry;

    registry.registerComponent<Position>();
    registry.registerComponent<Velocity>();
    registry.registerComponent<Drawable>();
    registry.registerComponent<Controllable>();

    return 0;
}
