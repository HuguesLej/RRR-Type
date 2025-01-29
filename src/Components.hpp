/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
    #define COMPONENTS_HPP_

namespace comp
{
    struct Position
    {
        float x;
        float y;

        Position(float x = 0, float y = 0) : x(x), y(y) {}
    };

    struct Velocity
    {
        float x;
        float y;

        Velocity(float x = 0, float y = 0) : x(x), y(y) {}
    };

    struct Drawable
    {
        Drawable() = default;
    };

    struct Controllable
    {
        Controllable() = default;
    };
}

#endif /* !COMPONENTS_HPP_ */
