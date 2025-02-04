/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
    #define POSITIONSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "../RegistryManager.hpp"

class PositionSystem : public ASystem
{
    public:
        PositionSystem() = default;
        ~PositionSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, uint64_t elapsedMs) override
        {
            (void) graphical;

            try {

                auto &positions = manager.getComponents<comp::Position>();
                auto &velocities = manager.getComponents<comp::Velocity>();

                try {

                    auto &colliders = manager.getComponents<comp::Collider>();

                    handlePositions(positions, velocities, colliders, elapsedMs);

                } catch (std::exception const &e) {

                    (void) e;

                    auto tmpColliders = ComponentsRegistry<comp::Collider>();
                    auto &colliders = tmpColliders;

                    handlePositions(positions, velocities, colliders, elapsedMs);

                }

            } catch (RegistryManager::ComponentError const &e) {
                (void) e;
                throw ASystem::SystemError("PositionSystem", std::vector<std::string>{"Position", "Velocity"});
            }
        }

    private:

        void handlePositions(ComponentsRegistry<comp::Position> &positions, ComponentsRegistry<comp::Velocity> const &velocities,
            ComponentsRegistry<comp::Collider> const &colliders, uint64_t const &elapsedMs)
        {
            for (std::size_t i = 0; i < positions.size(); i++) {

                if (!positions[i] || velocities.size() <= i || !velocities[i]) {
                    continue;
                }

                auto velPosX = velocities[i]->posX;
                auto velNegX = velocities[i]->negX;
                auto velPosY = velocities[i]->posY;
                auto velNegY = velocities[i]->negY;

                if (colliders.size() > i && colliders[i]) {

                    if (colliders[i]->collidePosX) {
                        velPosX = 0;
                    }
                    if (colliders[i]->collideNegX) {
                        velNegX = 0;
                    }
                    if (colliders[i]->collidePosY) {
                        velPosY = 0;
                    }
                    if (colliders[i]->collideNegY) {
                        velNegY = 0;
                    }

                }

                positions[i]->x += (velPosX - velNegX) * elapsedMs / 10;
                positions[i]->y += (velPosY - velNegY) * elapsedMs / 10;

            }
        }
};

#endif /* !POSITIONSYSTEM_HPP_ */
