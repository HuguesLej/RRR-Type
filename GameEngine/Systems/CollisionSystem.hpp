/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
    #define COLLISIONSYSTEM_HPP_

    #include <algorithm>
    #include <limits>
    #include "ASystem.hpp"
    #include "../RegistryManager.hpp"

class CollisionSystem : public ASystem
{
    public:
        CollisionSystem() = default;
        ~CollisionSystem() = default;

        struct HitBox {
            float minX;
            float minY;
            float maxX;
            float maxY;

            HitBox(float minX, float minY, float maxX, float maxY) : minX(minX), minY(minY), maxX(maxX), maxY(maxY) {}
        };

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, float elapsedSeconds) override
        {
            (void) graphical;

            auto &positions = manager.getComponents<comp::Position>();
            auto &velocities = manager.getComponents<comp::Velocity>();
            auto &colliders = manager.getComponents<comp::Collider>();

            for (size_t i = 0; i < positions.size(); i++) {
                if (positions[i] && colliders[i]) {
                    colliders[i]->collidePosX = false;
                    colliders[i]->collideNegX = false;
                    colliders[i]->collidePosY = false;
                    colliders[i]->collideNegY = false;

                    for (size_t j = 0; j < positions.size(); j++) {
                        if (i == j) {
                            continue;
                        }
                        if (positions[j] && colliders[j]) {
                            auto layerI = std::find(colliders[j]->collidingLayers.begin(), colliders[j]->collidingLayers.end(), colliders[i]->layer);
                            auto layerJ = std::find(colliders[i]->collidingLayers.begin(), colliders[i]->collidingLayers.end(), colliders[j]->layer);

                            if (layerI == colliders[j]->collidingLayers.end() && layerJ == colliders[i]->collidingLayers.end()) {
                                colliders[i]->collidePosX = false;
                                colliders[i]->collideNegX = false;
                                colliders[i]->collidePosY = false;
                                colliders[i]->collideNegY = false;
                            } else {
                                HitBox hbI(
                                    positions[i]->x - colliders[i]->width / 2,
                                    positions[i]->y - colliders[i]->height / 2,
                                    positions[i]->x + colliders[i]->width / 2,
                                    positions[i]->y + colliders[i]->height / 2
                                );
                                HitBox hbJ(
                                    positions[j]->x - colliders[j]->width / 2,
                                    positions[j]->y - colliders[j]->height / 2,
                                    positions[j]->x + colliders[j]->width / 2,
                                    positions[j]->y + colliders[j]->height / 2
                                );

                                std::string collisionFace = "None";
                                float minPenetration = std::numeric_limits<float>::max();

                                if (hbI.minX <= hbJ.maxX && hbI.maxX >= hbJ.minX && hbI.minY <= hbJ.maxY && hbI.maxY >= hbJ.minY) {
                                    float penetrationPosX = hbI.maxX - hbJ.minX;
                                    float penetrationNegX = hbJ.maxX - hbI.minX;
                                    float penetrationPosY = hbI.maxY - hbJ.minY;
                                    float penetrationNegY = hbJ.maxY - hbI.minY;

                                    if (penetrationPosX >= 0 && penetrationPosX < minPenetration) {
                                        minPenetration = penetrationPosX;
                                        collisionFace = "PosX";
                                    }
                                    if (penetrationNegX >= 0 && penetrationNegX < minPenetration) {
                                        minPenetration = penetrationNegX;
                                        collisionFace = "NegX";
                                    }
                                    if (penetrationPosY >= 0 && penetrationPosY < minPenetration) {
                                        minPenetration = penetrationPosY;
                                        collisionFace = "PosY";
                                    }
                                    if (penetrationNegY >= 0 && penetrationNegY < minPenetration) {
                                        minPenetration = penetrationNegY;
                                        collisionFace = "NegY";
                                    }
                                }

                                if (minPenetration == 0) {
                                    collisionFace = "None";
                                }
                                if (collisionFace == "PosX") {
                                    colliders[i]->collidePosX = true;
                                } else if (collisionFace == "NegX") {
                                    colliders[i]->collideNegX = true;
                                } else if (collisionFace == "PosY") {
                                    colliders[i]->collidePosY = true;
                                } else if (collisionFace == "NegY") {
                                    colliders[i]->collideNegY = true;
                                }

                                if (velocities.size() > i && velocities[i]) {
                                    if (colliders[i]->collidePosX) {
                                        positions[i]->x = hbJ.minX - colliders[i]->width / 2;
                                    }
                                    if (colliders[i]->collideNegX) {
                                        positions[i]->x = hbJ.maxX + colliders[i]->width / 2;
                                    }
                                    if (colliders[i]->collidePosY) {
                                        positions[i]->y = hbJ.minY - colliders[i]->height / 2;
                                    }
                                    if (colliders[i]->collideNegY) {
                                        positions[i]->y = hbJ.maxY - colliders[i]->height / 2;
                                    }
                                }
                            }
                        }
                    }

                }
            }
        }

};

#endif /* !COLLISIONSYSTEM_HPP_ */
