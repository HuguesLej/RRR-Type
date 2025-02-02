/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
    #define COMPONENTS_HPP_

    #include <cstdint>

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
        std::uint32_t textureId;
        float scaleX;
        float scaleY;
        float rotation;

        Drawable(std::uint32_t textureId, float scaleX = 1.0, float scaleY = 1.0, float rotation = 0)
            : textureId(textureId), scaleX(scaleX), scaleY(scaleY), rotation(rotation) {};
    };

    struct Animable
    {
        std::uint32_t framesNumber;
        std::uint32_t currentFrame;

        Animable(std::uint32_t framesNumber) : framesNumber(framesNumber), currentFrame(0) {};
    };

    struct Controllable
    {
        Controllable() = default;
    };
}

#endif /* !COMPONENTS_HPP_ */
