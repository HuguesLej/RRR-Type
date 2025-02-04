/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
    #define POSITIONSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "RegistryManager.hpp"

class PositionSystem : public ASystem
{
    public:
        PositionSystem() = default;
        ~PositionSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, uint64_t elapsedMs) override;

    private:
        void handlePositions(ComponentsRegistry<comp::Position> &positions, ComponentsRegistry<comp::Velocity> const &velocities,
            ComponentsRegistry<comp::Collider> const &colliders, uint64_t const &elapsedMs);
};

#endif /* !POSITIONSYSTEM_HPP_ */
