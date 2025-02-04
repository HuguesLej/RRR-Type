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

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, uint64_t elapsedMs) override;

    private:
        void handleDraw(std::shared_ptr<AGraphical> &graphical, ComponentsRegistry<comp::Position> const &positions,
            ComponentsRegistry<comp::Drawable> const &drawables, ComponentsRegistry<comp::Animable> &animables, uint64_t &elapsedMs);
};

#endif /* !DRAWSYSTEM_HPP_ */
