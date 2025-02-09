/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** DrawSystem
*/

#ifndef DRAWSYSTEM_HPP_
    #define DRAWSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "RegistryManager.hpp"

class DrawSystem : public ASystem
{
    public:
        DrawSystem() = default;
        ~DrawSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs) override;

    private:
        void handleDraw(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &nComm, ComponentsRegistry<comp::Position> const &pos, 
            ComponentsRegistry<comp::Drawable> &draw, ComponentsRegistry<comp::Animable> &anim, uint64_t &elapsedMs);

        void handleView(std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &nComm, comp::Position const &position,
            comp::Controllable const &controllable, bool &viewHasChanged);

        ComponentsRegistry<comp::Controllable> getControllables(RegistryManager &manager);
        ComponentsRegistry<comp::Velocity> getVelocities(RegistryManager &manager);
};

#endif /* !DRAWSYSTEM_HPP_ */
