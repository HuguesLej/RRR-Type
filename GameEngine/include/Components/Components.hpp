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
    #include "Keys.hpp"

class ComponentsSerializer;

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

        private:
            Drawable() : textureId(0), scaleX(1.0), scaleY(1.0), rotation(0) {}
            friend ComponentsSerializer;
    };

    struct Animable
    {
        uint32_t framesNumber;
        uint32_t currentFrame = 0;

        uint64_t cooldownMs;
        uint64_t elapsedTimeMs = 0;

        Animable(uint32_t framesNumber, uint64_t cooldownMs = 0) : framesNumber(framesNumber), cooldownMs(cooldownMs) {}

        private:
            Animable() : framesNumber(0), cooldownMs(0) {}
            friend ComponentsSerializer;
    };

    struct Controllable
    {
        std::pair<Keys, bool> left;
        std::pair<Keys, bool> right;
        std::pair<Keys, bool> up;
        std::pair<Keys, bool> down;
        std::pair<Keys, bool> jump;
        std::string localAdress = "";
        uint16_t localPort = 0;

        Controllable(Keys left, Keys right, Keys up, Keys down, Keys jump)
            : left({left, false}), right({right, false}), up({up, false}), down({down, false}), jump({jump, false}) {}
        Controllable(Keys left, Keys right, Keys up, Keys down, Keys jump, std::string localAdress, uint16_t localPort)
            : left({left, false}), right({right, false}), up({up, false}), down({down, false}), jump({jump, false}), localAdress(localAdress), localPort(localPort) {}

        private:
            Controllable() : left({Keys::None, false}), right({Keys::None, false}), up({Keys::None, false}), down({Keys::None, false}), jump({Keys::None, false}) {}
            friend ComponentsSerializer;
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
            : width(width), height(height), layer(layer), collisionGivenDamage(collisionGivenDamage) {
                this->collidingLayers = {layer};
                this->collidingLayers.insert(this->collidingLayers.end(), collidingLayers.begin(), collidingLayers.end());
            }

        private:
            Collider() : width(0), height(0), layer(0), collisionGivenDamage(0) {}
            friend ComponentsSerializer;
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
