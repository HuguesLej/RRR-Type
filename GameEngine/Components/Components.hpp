/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
    #define COMPONENTS_HPP_

    #include <cstdint>
    #include <vector>
    #include "../Keys.hpp"

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
        float negX;
        float posX;
        float negY;
        float posY;

        Velocity(float x = 0, float y = 0) : negX(-x), posX(x), negY(-y), posY(y) {}
    };

    struct Drawable
    {
        std::uint32_t textureId;
        float scaleX;
        float scaleY;
        float rotation;

        Drawable(std::uint32_t textureId, float scaleX = 1.0, float scaleY = 1.0, float rotation = 0)
            : textureId(textureId), scaleX(scaleX), scaleY(scaleY), rotation(rotation) {}
    };

    struct Animable
    {
        std::uint32_t framesNumber;
        std::uint32_t currentFrame;

        Animable(std::uint32_t framesNumber) : framesNumber(framesNumber), currentFrame(0) {}
    };

    struct Controllable
    {
        Keys left = Keys::Unknown;
        Keys right = Keys::Unknown;
        Keys up = Keys::Unknown;
        Keys down = Keys::Unknown;
        Keys jump = Keys::Unknown;
        float maxVelocity;

        Controllable(Keys left, Keys right, Keys up, Keys down, Keys jump, float maxVelocity = 0)
            : left(left), right(right), up(up), down(down), jump(jump), maxVelocity(maxVelocity) {}
    };

    struct Collider
    {
        float width;
        float height;
        std::uint32_t layer;
        std::vector<std::uint32_t> collidingLayers;

        Collider(float width, float height, std::uint32_t layer, std::vector<std::uint32_t> collidingLayers)
            : width(width), height(height), layer(layer), collidingLayers(collidingLayers) {}
    };
}

#endif /* !COMPONENTS_HPP_ */
