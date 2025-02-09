/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** DrawSystem
*/

#include "DrawSystem.hpp"

void DrawSystem::update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &networkCommunication, uint64_t elapsedMs)
{
    try {

        auto &positions = manager.getComponents<comp::Position>();
        auto &drawables = manager.getComponents<comp::Drawable>();

        try {

            auto &animables = manager.getComponents<comp::Animable>();
            auto controllables = getControllables(manager);

            handleDraw(graphical, networkCommunication, positions, drawables, animables, controllables, elapsedMs);

        } catch (RegistryManager::ComponentError const &e) {

            (void) e;

            auto tmpAnimables = ComponentsRegistry<comp::Animable>();
            auto &animables = tmpAnimables;
            auto controllables = getControllables(manager);

            handleDraw(graphical, networkCommunication, positions, drawables, animables, controllables, elapsedMs);

        }

    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        throw ASystem::SystemError("DrawSystem", std::vector<std::string>{"Position", "Drawable"});
    }
}

void DrawSystem::handleDraw(std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &nComm, ComponentsRegistry<comp::Position> const &pos, 
    ComponentsRegistry<comp::Drawable> const &draw, ComponentsRegistry<comp::Animable> &anim, ComponentsRegistry<comp::Controllable> &ctrl, uint64_t &elapsedMs)
{
    bool viewHasChanged = false;

    for (std::size_t i = 0; i < pos->size(); i++) {

        if (!pos[i] || draw->size() <= i || !draw[i]) {
            continue;
        }

        if (!viewHasChanged && ctrl->size() > i && ctrl[i]) {
            if (nComm && !nComm->isServer()) {
                auto local = nComm->getLocalAddressAndPort();

                if (local.first == ctrl[i]->localAdress && local.second == ctrl[i]->localPort) {
                    graphical->setViewCenter(pos[i].value());
                    viewHasChanged = true;
                }
            } else {
                graphical->setViewCenter(pos[i].value());
                viewHasChanged = true;
            }
        }

        if (anim->size() > i && anim[i]) {
            graphical->drawSprite(pos[i].value(), draw[i].value(), anim[i].value(), elapsedMs);
        } else {
            graphical->drawSprite(pos[i].value(), draw[i].value());
        }
    }
}

ComponentsRegistry<comp::Controllable> DrawSystem::getControllables(RegistryManager &manager)
{
    try {
        return manager.getComponents<comp::Controllable>();
    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        return ComponentsRegistry<comp::Controllable>();
    }
}
