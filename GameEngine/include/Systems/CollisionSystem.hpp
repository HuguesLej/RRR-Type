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
    #include "RegistryManager.hpp"

class CollisionSystem : public ASystem
{
    public:
        CollisionSystem() = default;
        ~CollisionSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs) override;

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


        void handleCollisions(comp::Position &pos1, comp::Position &pos2, comp::Collider &collider1, comp::Collider &collider2, comp::Velocity const *vel1);

        CollisionFace findCollidingFace(HitBox const &h1, HitBox const &h2);

        void updateCollider(comp::Collider &collider, CollisionFace const &collisionFace);
        void updatePosition(comp::Position &pos, comp::Collider const &collider, HitBox const &otherHb, CollisionFace const &collisionFace);
};

#endif /* !COLLISIONSYSTEM_HPP_ */
