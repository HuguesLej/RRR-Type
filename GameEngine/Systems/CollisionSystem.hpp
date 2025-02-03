/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
    #define COLLISIONSYSTEM_HPP_

    #include <algorithm>
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

                                // colliders[i]->collidePosX = isCollidingOnFace(hbI.maxX, hbI.minY, hbI.maxX, hbI.maxY, hbJ);
                                // colliders[i]->collideNegX = isCollidingOnFace(hbI.minX, hbI.minY, hbI.minX, hbI.maxY, hbJ);
                                // colliders[i]->collidePosY = isCollidingOnFace(hbI.minX, hbI.maxY, hbI.maxX, hbI.maxY, hbJ);
                                // colliders[i]->collideNegY = isCollidingOnFace(hbI.minX, hbI.minY, hbI.maxX, hbI.minY, hbJ);

                                bool overlapX = hbI.minX <= hbJ.maxX && hbI.maxX >= hbJ.minX;
                                bool overlapY = hbI.minY <= hbJ.maxY && hbI.maxY >= hbJ.minY;

                                if (hbI.maxX >= hbJ.minX && hbI.maxX <= hbJ.maxX && overlapY) {
                                    colliders[i]->collidePosX = true;
                                }
                                if (hbI.minX >= hbJ.minX && hbI.minX <= hbJ.maxX && overlapY) {
                                    colliders[i]->collideNegX = true;
                                }
                                if (hbI.maxY >= hbJ.minY && hbI.maxY <= hbJ.maxY && overlapX) {
                                    colliders[i]->collidePosY = true;
                                }
                                if (hbI.minY >= hbJ.minY && hbI.minY <= hbJ.maxY && overlapX) {
                                    colliders[i]->collideNegY = true;
                                }

                                // // PosX
                                // if (hbI.maxX >= hbJ.minX && hbI.maxX <= hbJ.maxX) {
                                //     if ((hbI.minY >= hbJ.minY && hbI.minY <= hbJ.maxY) || (hbI.maxY >= hbJ.minY && hbI.maxY <= hbJ.maxY)) {
                                //         colliders[i]->collidePosX = true;
                                //     }
                                //     if ((hbJ.minY >= hbI.minY && hbJ.minY <= hbI.maxY) || (hbJ.maxY >= hbI.minY && hbJ.maxY <= hbI.maxY)) {
                                //         colliders[i]->collidePosX = true;
                                //     }
                                // }
                                // // NegX
                                // if (hbI.minX >= hbJ.minX && hbI.minX <= hbJ.maxX) {
                                //     if ((hbI.minY >= hbJ.minY && hbI.minY <= hbJ.maxY) || (hbI.maxY >= hbJ.minY && hbI.maxY <= hbJ.maxY)) {
                                //         colliders[i]->collideNegX = true;
                                //     }
                                //     if ((hbJ.minY >= hbI.minY && hbJ.minY <= hbI.maxY) || (hbJ.maxY >= hbI.minY && hbJ.maxY <= hbI.maxY)) {
                                //         colliders[i]->collideNegX = true;
                                //     }
                                // }
                                // // PosY
                                // if (hbI.maxY >= hbJ.minY && hbI.maxY <= hbJ.maxY) {
                                //     if ((hbI.minX >= hbJ.minX && hbI.minX <= hbJ.maxX) || (hbI.maxX >= hbJ.minX && hbI.maxX <= hbJ.maxX)) {
                                //         colliders[i]->collidePosY = true;
                                //     }
                                //     if ((hbJ.minX >= hbI.minX && hbJ.minX <= hbI.maxX) || (hbJ.maxX >= hbI.minX && hbJ.maxX <= hbI.maxX)) {
                                //         colliders[i]->collidePosY = true;
                                //     }
                                // }
                                // // NegY
                                // if (hbI.minY >= hbJ.minY && hbI.minY <= hbJ.maxY) {
                                //     if ((hbI.minX >= hbJ.minX && hbI.minX <= hbJ.maxX) || (hbI.maxX >= hbJ.minX && hbI.maxX <= hbJ.maxX)) {
                                //         colliders[i]->collideNegY = true;
                                //     }
                                //     if ((hbJ.minX >= hbI.minX && hbJ.minX <= hbI.maxX) || (hbJ.maxX >= hbI.minX && hbJ.maxX <= hbI.maxX)) {
                                //         colliders[i]->collideNegY = true;
                                //     }
                                // }

                                if (i == 0) {
                                    std::cout << std::endl;
                                    std::cout << "posX: " << (colliders[i]->collidePosX ? "true" : "false") << std::endl;
                                    std::cout << "negX: " << (colliders[i]->collideNegX ? "true" : "false") << std::endl;
                                    std::cout << "posY: " << (colliders[i]->collidePosY ? "true" : "false") << std::endl;
                                    std::cout << "negY: " << (colliders[i]->collideNegY ? "true" : "false") << std::endl;
                                    std::cout << std::endl;
                                }

                                // if (velocities.size() > i && velocities[i]) {
                                //     if (colliders[i]->collidePosX) {
                                //         positions[i]->x = hbJ.minX - colliders[i]->width / 2;
                                //     }
                                //     if (colliders[i]->collideNegX) {
                                //         positions[i]->x = hbJ.maxX + colliders[i]->width / 2;
                                //     }
                                //     if (colliders[i]->collidePosY) {
                                //         positions[i]->y = hbJ.minY - colliders[i]->height / 2;
                                //     }
                                //     if (colliders[i]->collideNegY) {
                                //         positions[i]->y = hbJ.maxY - colliders[i]->height / 2;
                                //     }
                                // }
                            }
                        } else {
                            colliders[i]->collidePosX = false;
                            colliders[i]->collideNegX = false;
                            colliders[i]->collidePosY = false;
                            colliders[i]->collideNegY = false;
                        }
                    }

                }
            }
        }

        // bool isCollidingOnFace(float const x1, float const y1, float const x2, float const y2, HitBox const &h)
        // {
        //     if (x1 >= h.minX && x1 <= h.maxX && y1 >= h.minY && y1 <= h.maxY) {
        //         return true;
        //     }
        //     if (x2 >= h.minX && x2 <= h.maxX && y2 >= h.minY && y2 <= h.maxY) {
        //         return true;
        //     }
        //     return false;
        // }
};

#endif /* !COLLISIONSYSTEM_HPP_ */
