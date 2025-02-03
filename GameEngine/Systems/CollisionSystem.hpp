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

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, float elapsedSeconds) override
        {
            (void) graphical;
            (void) elapsedSeconds;

            try {

                auto &positions = manager.getComponents<comp::Position>();
                auto &velocities = manager.getComponents<comp::Velocity>();
                auto &colliders = manager.getComponents<comp::Collider>();

                for (size_t i = 0; i < positions.size(); i++) {
                    if (!positions[i] || !colliders[i]) {
                        continue;
                    }

                    colliders[i]->collidePosX = false;
                    colliders[i]->collideNegX = false;
                    colliders[i]->collidePosY = false;
                    colliders[i]->collideNegY = false;

                    for (size_t j = 0; j < positions.size(); j++) {
                        if (i == j) {
                            continue;
                        }

                        if (!positions[j] || !colliders[j]) {
                            continue;
                        }

                        auto layerI = std::find(colliders[j]->collidingLayers.begin(), colliders[j]->collidingLayers.end(), colliders[i]->layer);
                        auto layerJ = std::find(colliders[i]->collidingLayers.begin(), colliders[i]->collidingLayers.end(), colliders[j]->layer);

                        if (layerI == colliders[j]->collidingLayers.end() && layerJ == colliders[i]->collidingLayers.end()) {
                            continue;
                        }

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

                        CollisionFace collisionFace = findCollidingFace(hbI, hbJ);

                        switch (collisionFace) {
                            case CollisionFace::POSX:
                                colliders[i]->collidePosX = true;
                                break;
                            case CollisionFace::NEGX:
                                colliders[i]->collideNegX = true;
                                break;
                            case CollisionFace::POSY:
                                colliders[i]->collidePosY = true;
                                break;
                            case CollisionFace::NEGY:
                                colliders[i]->collideNegY = true;
                                break;
                            default:
                                break;
                        }

                        if (velocities.size() > i && velocities[i]) {
                            switch (collisionFace) {
                                case CollisionFace::POSX:
                                    positions[i]->x = hbJ.minX - colliders[i]->width / 2;
                                    break;
                                case CollisionFace::NEGX:
                                    positions[i]->x = hbJ.maxX + colliders[i]->width / 2;
                                    break;
                                case CollisionFace::POSY:
                                    positions[i]->y = hbJ.minY - colliders[i]->height / 2;
                                    break;
                                case CollisionFace::NEGY:
                                    positions[i]->y = hbJ.maxY + colliders[i]->height / 2;
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }

            } catch (RegistryManager::ComponentError const &e) {
                (void) e;
                throw ASystem::SystemError("CollisionSystem", std::vector<std::string>{"Position", "Velocity", "Collider"});
            }
        }

    private:

        struct HitBox {
            float minX;
            float minY;
            float maxX;
            float maxY;

            HitBox(float minX, float minY, float maxX, float maxY) : minX(minX), minY(minY), maxX(maxX), maxY(maxY) {}
        };

        enum CollisionFace
        {
            NONE,
            POSX,
            NEGX,
            POSY,
            NEGY
        };

        CollisionFace findCollidingFace(HitBox const &h1, HitBox const &h2)
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

            if (minPenetration == 0) {
                return CollisionFace::NONE;
            }

            return collisionFace;
        }

};

#endif /* !COLLISIONSYSTEM_HPP_ */
