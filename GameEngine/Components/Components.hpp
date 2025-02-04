/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
    #define COMPONENTS_HPP_

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

        Velocity(float x = 0, float y = 0) : negX(x), posX(x), negY(y), posY(y) {}
    };

    struct Drawable
    {
        uint32_t textureId;
        float scaleX;
        float scaleY;
        float rotation;

        Drawable(uint32_t textureId, float scaleX = 1.0, float scaleY = 1.0, float rotation = 0)
            : textureId(textureId), scaleX(scaleX), scaleY(scaleY), rotation(rotation) {}
    };

    struct Animable
    {
        uint32_t framesNumber;
        uint32_t currentFrame = 0;

        uint64_t cooldownMs;
        uint64_t elapsedTimeMs = 0;

        Animable(uint32_t framesNumber, uint64_t cooldownMs = 0) : framesNumber(framesNumber), cooldownMs(cooldownMs) {}
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

        uint32_t layer;
        std::vector<uint32_t> collidingLayers;

        bool collidePosX = false;
        bool collideNegX = false;
        bool collidePosY = false;
        bool collideNegY = false;

        uint32_t collisionGivenDamage;
        uint32_t collisionTakenDamage = 0;

        Collider(float width, float height, uint32_t layer, std::vector<uint32_t> collidingLayers, uint32_t collisionGivenDamage = 0)
            : width(width), height(height), layer(layer), collidingLayers(collidingLayers), collisionGivenDamage(collisionGivenDamage) {}
    };

    struct Gravity
    {
        float velocity;

        Gravity(float velocity = 0) : velocity(velocity) {}
    };

    struct Jumpable
    {
        float velocity;
        uint64_t durationMs;
        uint64_t elapsedTimeMs = 0;

        Jumpable(float velocity = 0, uint64_t durationMs = 0) : velocity(velocity), durationMs(durationMs) {}
    };

    struct Health
    {
        uint32_t health;
        uint32_t maxHealth;

        Health(uint32_t maxHealth = 1, uint32_t health = 1) : health(health), maxHealth(maxHealth) {
            if (health > maxHealth) {
                this->health = maxHealth;
            }
            if (health == 0) {
                this->health = 1;
            }
            if (maxHealth == 0) {
                this->maxHealth = 1;
            }
        }
    };

}

#endif /* !COMPONENTS_HPP_ */
