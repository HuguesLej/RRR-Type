/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** DrawSystem
*/

#include "DrawSystem.hpp"

void DrawSystem::update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs)
{
    (void) networkCommunication;

    try {

        auto &positions = manager.getComponents<comp::Position>();
        auto &drawables = manager.getComponents<comp::Drawable>();

        try {

            auto &animables = manager.getComponents<comp::Animable>();

            handleDraw(graphical, positions, drawables, animables, elapsedMs);

        } catch (RegistryManager::ComponentError const &e) {

            (void) e;

            auto tmpAnimables = ComponentsRegistry<comp::Animable>();
            auto &animables = tmpAnimables;

            handleDraw(graphical, positions, drawables, animables, elapsedMs);

        }

    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        throw ASystem::SystemError("DrawSystem", std::vector<std::string>{"Position", "Drawable"});
    }
}

void DrawSystem::handleDraw(std::shared_ptr<AGraphical> &graphical, ComponentsRegistry<comp::Position> const &positions,
    ComponentsRegistry<comp::Drawable> const &drawables, ComponentsRegistry<comp::Animable> &animables, uint64_t &elapsedMs)
{
    for (std::size_t i = 0; i < positions.size(); i++) {

        if (!positions[i] || drawables.size() <= i || !drawables[i]) {
            continue;
        }

        if (animables.size() > i && animables[i]) {
            graphical->drawSprite(positions[i].value(), drawables[i].value(), animables[i].value(), elapsedMs);
        } else {
            graphical->drawSprite(positions[i].value(), drawables[i].value());
        }
    }
}
