/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** ComponentsSerializer
*/

#include "ComponentsSerializer.hpp"

ComponentsSerializer::Error::Error(Type type)
{
    if (type == SERIALIZE) {
        _msg = "Error while serializing data. Passed data is not a valid ComponentsRegistry.";
    } else {
        _msg = "Error while deserializing data. Received data is not a valid ComponentsRegistry.";
    }
}

const char *ComponentsSerializer::Error::what() const noexcept
{
    return _msg.c_str();
}


void ComponentsSerializer::registerSerializers()
{
    registerComponent<comp::Position>();
    registerComponent<comp::Velocity>();
    registerComponent<comp::Drawable>();
    registerComponent<comp::Animable>();
    registerComponent<comp::Controllable>();
    registerComponent<comp::Collider>();
    registerComponent<comp::Gravity>();
    registerComponent<comp::Jumpable>();
    registerComponent<comp::Health>();
}


void ComponentsSerializer::serializeComponent(std::ostringstream &oss, const comp::Position &component)
{
    oss << component.x << " " << component.y << " ";
}

void ComponentsSerializer::deserializeComponent(std::istringstream &iss, comp::Position &component)
{
    iss >> component.x >> component.y;
}


void ComponentsSerializer::serializeComponent(std::ostringstream &oss, const comp::Velocity &component)
{
    oss << component.negX << " " << component.posX << " " << component.negY << " " << component.posY << " ";
}

void ComponentsSerializer::deserializeComponent(std::istringstream &iss, comp::Velocity &component)
{
    iss >> component.negX >> component.posX >> component.negY >> component.posY;
}


void ComponentsSerializer::serializeComponent(std::ostringstream &oss, const comp::Drawable &component)
{
    oss << component.textureId << " " << component.scaleX << " " << component.scaleY << " " << component.rotation << " ";
}

void ComponentsSerializer::deserializeComponent(std::istringstream &iss, comp::Drawable &component)
{
    iss >> component.textureId >> component.scaleX >> component.scaleY >> component.rotation;
}


void ComponentsSerializer::serializeComponent(std::ostringstream &oss, const comp::Animable &component)
{
    oss << component.framesNumber << " " << component.currentFrame << " " << component.cooldownMs << " " << component.elapsedTimeMs << " ";
}

void ComponentsSerializer::deserializeComponent(std::istringstream &iss, comp::Animable &component)
{
    iss >> component.framesNumber >> component.currentFrame >> component.cooldownMs >> component.elapsedTimeMs;
}


void ComponentsSerializer::serializeComponent(std::ostringstream &oss, const comp::Controllable &component)
{
    oss << static_cast<int>(component.left.first) << " " << component.left.second << " ";
    oss << static_cast<int>(component.right.first) << " " << component.right.second << " ";
    oss << static_cast<int>(component.up.first) << " " << component.up.second << " ";
    oss << static_cast<int>(component.down.first) << " " << component.down.second << " ";
    oss << static_cast<int>(component.jump.first) << " " << component.jump.second << " ";
    oss << component.maxVelocity << " ";
}

void ComponentsSerializer::deserializeComponent(std::istringstream &iss, comp::Controllable &component)
{
    int leftKey;
    int rightKey;
    int upKey;
    int downKey;
    int jumpKey;
    bool leftBool;
    bool rightBool;
    bool upBool;
    bool downBool;
    bool jumpBool;

    iss >> leftKey >> leftBool >> rightKey >> rightBool >> upKey >> upBool >> downKey >> downBool >> jumpKey >> jumpBool >> component.maxVelocity;
    component.left = {static_cast<Keys>(leftKey), leftBool};
    component.right = {static_cast<Keys>(rightKey), rightBool};
    component.up = {static_cast<Keys>(upKey), upBool};
    component.down = {static_cast<Keys>(downKey), downBool};
    component.jump = {static_cast<Keys>(jumpKey), jumpBool};
}


void ComponentsSerializer::serializeComponent(std::ostringstream &oss, const comp::Collider &component)
{
    oss << component.width << " " << component.height << " " << component.layer << " " << component.collidingLayers.size() << " ";
    for (auto &layer : component.collidingLayers) {
        oss << layer << " ";
    }
    oss << component.collideNegX << " " << component.collidePosX << " " << component.collideNegY << " " << component.collidePosY << " ";
    oss << component.collisionGivenDamage << " " << component.collisionTakenDamage << " ";
}

void ComponentsSerializer::deserializeComponent(std::istringstream &iss, comp::Collider &component)
{
    size_t collidingLayersSize;

    iss >> component.width >> component.height >> component.layer >> collidingLayersSize;
    for (size_t i = 0; i < collidingLayersSize; i++) {
        uint32_t layer;
        iss >> layer;
        component.collidingLayers.push_back(layer);
    }
    iss >> component.collideNegX >> component.collidePosX >> component.collideNegY >> component.collidePosY;
    iss >> component.collisionGivenDamage >> component.collisionTakenDamage;
}


void ComponentsSerializer::serializeComponent(std::ostringstream &oss, const comp::Gravity &component)
{
    oss << component.velocity << " ";
}

void ComponentsSerializer::deserializeComponent(std::istringstream &iss, comp::Gravity &component)
{
    iss >> component.velocity;
}


void ComponentsSerializer::serializeComponent(std::ostringstream &oss, const comp::Jumpable &component)
{
    oss << component.velocity << " " << component.durationMs << " " << component.elapsedTimeMs << " ";
}

void ComponentsSerializer::deserializeComponent(std::istringstream &iss, comp::Jumpable &component)
{
    iss >> component.velocity >> component.durationMs >> component.elapsedTimeMs;
}


void ComponentsSerializer::serializeComponent(std::ostringstream &oss, const comp::Health &component)
{
    oss << component.health << " " << component.maxHealth << " ";
}

void ComponentsSerializer::deserializeComponent(std::istringstream &iss, comp::Health &component)
{
    iss >> component.health >> component.maxHealth;
}
