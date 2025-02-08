/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

void CollisionSystem::update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs)
{
    (void) graphical;
    (void) networkCommunication;
    (void) elapsedMs;

    try {

        auto &positions = manager.getComponents<comp::Position>();
        auto &velocities = manager.getComponents<comp::Velocity>();
        auto &colliders = manager.getComponents<comp::Collider>();

        for (size_t i = 0; i < positions.size(); i++) {

            if (!positions[i] || colliders.size() <= i || !colliders[i]) {
                continue;
            }

            colliders[i]->collidePosX = false;
            colliders[i]->collideNegX = false;
            colliders[i]->collidePosY = false;
            colliders[i]->collideNegY = false;
            colliders[i]->collisionTakenDamage = 0;

            for (size_t j = 0; j < positions.size(); j++) {

                if (i == j || !positions[j] || colliders.size() <= j || !colliders[j]) {
                    continue;
                }

                auto layerI = std::find(colliders[j]->collidingLayers.begin(), colliders[j]->collidingLayers.end(), colliders[i]->layer);
                auto layerJ = std::find(colliders[i]->collidingLayers.begin(), colliders[i]->collidingLayers.end(), colliders[j]->layer);

                if (layerI == colliders[j]->collidingLayers.end() && layerJ == colliders[i]->collidingLayers.end()) {
                    continue;
                }

                handleCollisions(
                    positions[i].value(),
                    positions[j].value(),
                    colliders[i].value(),
                    colliders[j].value(),
                    velocities.size() > i ? (velocities[i] ? &velocities[i].value() : nullptr) : nullptr
                );

            }
        }

    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        throw ASystem::SystemError("CollisionSystem", std::vector<std::string>{"Position", "Velocity", "Collider"});
    }
}

void CollisionSystem::handleCollisions(comp::Position &pos1, comp::Position &pos2, comp::Collider &collider1, comp::Collider &collider2, comp::Velocity const *vel1)
{
    HitBox hb1(
        pos1.x - collider1.width / 2,
        pos1.y - collider1.height / 2,
        pos1.x + collider1.width / 2,
        pos1.y + collider1.height / 2
    );
    HitBox hb2(
        pos2.x - collider2.width / 2,
        pos2.y - collider2.height / 2,
        pos2.x + collider2.width / 2,
        pos2.y + collider2.height / 2
    );

    CollisionFace collisionFace = findCollidingFace(hb1, hb2);

    if (collisionFace != CollisionFace::NONE) {
        collider1.collisionTakenDamage += collider2.collisionGivenDamage;
    }

    updateCollider(collider1, collisionFace);

    if (vel1 != nullptr) {
        updatePosition(pos1, collider1, hb2, collisionFace);
    }
}


CollisionSystem::CollisionFace CollisionSystem::findCollidingFace(HitBox const &h1, HitBox const &h2)
{
    CollisionFace collisionFace = CollisionFace::NONE;
    bool overlapX = h1.minX <= h2.maxX && h1.maxX >= h2.minX;
    bool overlapY = h1.minY <= h2.maxY && h1.maxY >= h2.minY;

    if (!overlapX || !overlapY) {
        return CollisionFace::NONE;
    }

    float minPenetration = std::numeric_limits<float>::max();
    float penetrationPosX = h1.maxX - h2.minX;
    float penetrationNegX = h2.maxX - h1.minX;
    float penetrationPosY = h1.maxY - h2.minY;
    float penetrationNegY = h2.maxY - h1.minY;

    if (penetrationPosX >= 0 && penetrationPosX < minPenetration) {
        minPenetration = penetrationPosX;
        collisionFace = CollisionFace::POSX;
    }
    if (penetrationNegX >= 0 && penetrationNegX < minPenetration) {
        minPenetration = penetrationNegX;
        collisionFace = CollisionFace::NEGX;
    }
    if (penetrationPosY >= 0 && penetrationPosY < minPenetration) {
        minPenetration = penetrationPosY;
        collisionFace = CollisionFace::POSY;
    }
    if (penetrationNegY >= 0 && penetrationNegY < minPenetration) {
        minPenetration = penetrationNegY;
        collisionFace = CollisionFace::NEGY;
    }

    return collisionFace;
}


void CollisionSystem::updateCollider(comp::Collider &collider, CollisionFace const &collisionFace)
{
    switch (collisionFace) {
        case CollisionFace::POSX:
            collider.collidePosX = true;
            break;
        case CollisionFace::NEGX:
            collider.collideNegX = true;
            break;
        case CollisionFace::POSY:
            collider.collidePosY = true;
            break;
        case CollisionFace::NEGY:
            collider.collideNegY = true;
            break;
        default:
            break;
    }
}

void CollisionSystem::updatePosition(comp::Position &pos, comp::Collider const &collider, HitBox const &otherHb, CollisionFace const &collisionFace)
{
    switch (collisionFace) {
        case CollisionFace::POSX:
            pos.x = otherHb.minX - collider.width / 2;
            break;
        case CollisionFace::NEGX:
            pos.x = otherHb.maxX + collider.width / 2;
            break;
        case CollisionFace::POSY:
            pos.y = otherHb.minY - collider.height / 2;
            break;
        case CollisionFace::NEGY:
            pos.y = otherHb.maxY + collider.height / 2;
            break;
        default:
            break;
    }
}
