/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
    #define POSITIONSYSTEM_HPP_

    #include <algorithm>
    #include "ASystem.hpp"
    #include "../RegistryManager.hpp"

class PositionSystem : public ASystem
{
    public:
        PositionSystem() = default;
        ~PositionSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, float elapsedSeconds) override
        {
            (void) graphical;

            auto &positions = manager.getComponents<comp::Position>();
            auto &velocities = manager.getComponents<comp::Velocity>();

            try {
                auto &colliders = manager.getComponents<comp::Collider>();

                for (std::size_t i = 0; i < positions.size(); i++) {
                    if (positions[i] && velocities[i]) {

                        if (colliders[i]) {

                            handleCollisions(positions, velocities, colliders, elapsedSeconds, i);

                            // for (size_t j = 0; j < positions.size(); j++) {
                            //     if (i == j) {
                            //         continue;
                            //     }
                            //     if (positions[j] && colliders[j]) {
                            //         auto collidingLayerI = std::find(colliders[j]->collidingLayers.begin(), colliders[j]->collidingLayers.end(), colliders[i]->layer);
                            //         auto collidingLayerJ = std::find(colliders[i]->collidingLayers.begin(), colliders[i]->collidingLayers.end(), colliders[j]->layer);

                            //         if (collidingLayerI == colliders[j]->collidingLayers.end() && collidingLayerJ == colliders[i]->collidingLayers.end()) {
                            //             positions[i]->x += (velocities[i]->negX + velocities[i]->posX) * elapsedSeconds;
                            //             positions[i]->y += (velocities[i]->negY + velocities[i]->posY) * elapsedSeconds;
                            //         }
                            //     }
                            // }

                        } else {

                            positions[i]->x += (velocities[i]->negX + velocities[i]->posX) * elapsedSeconds;
                            positions[i]->y += (velocities[i]->negY + velocities[i]->posY) * elapsedSeconds;

                        }
                    }
                }

            } catch (std::exception const &e) {
                (void) e;

                for (std::size_t i = 0; i < positions.size(); i++) {
                    if (positions[i] && velocities[i]) {
                        positions[i]->x += (velocities[i]->negX + velocities[i]->posX) * elapsedSeconds;
                        positions[i]->y += (velocities[i]->negY + velocities[i]->posY) * elapsedSeconds;
                    }
                }
            }
        }

    private:

        struct HitBox {
            float sX;
            float sY;
            float eX;
            float eY;

            HitBox(float sX, float sY, float eX, float eY) : sX(sX), sY(sY), eX(eX), eY(eY) {}
        };

        void handleCollisions(ComponentsRegistry<comp::Position> &positions, ComponentsRegistry<comp::Velocity> const &velocities,
            ComponentsRegistry<comp::Collider> const &colliders, float elapsedSeconds, std::size_t const compIdx)
        {
            for (size_t j = 0; j < positions.size(); j++) {
                if (compIdx == j) {
                    continue;
                }
                if (positions[j] && colliders[j]) {
                    auto layerIdx = std::find(colliders[j]->collidingLayers.begin(), colliders[j]->collidingLayers.end(), colliders[compIdx]->layer);
                    auto layerJ = std::find(colliders[compIdx]->collidingLayers.begin(), colliders[compIdx]->collidingLayers.end(), colliders[j]->layer);

                    if (layerIdx == colliders[j]->collidingLayers.end() && layerJ == colliders[compIdx]->collidingLayers.end()) {

                        positions[compIdx]->x += (velocities[compIdx]->negX + velocities[compIdx]->posX) * elapsedSeconds;
                        positions[compIdx]->y += (velocities[compIdx]->negY + velocities[compIdx]->posY) * elapsedSeconds;

                    } else {

                        HitBox hitBoxIdx(
                            positions[compIdx]->x - colliders[compIdx]->width / 2,
                            positions[compIdx]->y - colliders[compIdx]->height / 2,
                            positions[compIdx]->x + colliders[compIdx]->width / 2,
                            positions[compIdx]->y + colliders[compIdx]->height / 2
                        );
                        HitBox hitBoxJ(
                            positions[j]->x - colliders[j]->width / 2,
                            positions[j]->y - colliders[j]->height / 2,
                            positions[j]->x + colliders[j]->width / 2,
                            positions[j]->y + colliders[j]->height / 2
                        );

                        if (!doHitBoxesCollapse(hitBoxIdx, hitBoxJ)) {
                            positions[compIdx]->x += (velocities[compIdx]->negX + velocities[compIdx]->posX) * elapsedSeconds;
                            positions[compIdx]->y += (velocities[compIdx]->negY + velocities[compIdx]->posY) * elapsedSeconds;
                        }

                    }
                }
            }
        }

        bool doHitBoxesCollapse(HitBox const &h1, HitBox const &h2)
        {
            if (isPointInHitBox(h1.sX, h1.sY, h2)) {
                return true;
            }
            if (isPointInHitBox(h1.sX, h1.eY, h2)) {
                return true;
            }
            if (isPointInHitBox(h1.eX, h1.sY, h2)) {
                return true;
            }
            if (isPointInHitBox(h1.eX, h1.eY, h2)) {
                return true;
            }
            return false;
        }

        bool isPointInHitBox(float x, float y, HitBox const &hitbox)
        {
            return x > hitbox.sX && x < hitbox.eX && y > hitbox.sY && y < hitbox.eY;
        }
};

#endif /* !POSITIONSYSTEM_HPP_ */
