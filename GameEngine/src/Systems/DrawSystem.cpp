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

            handleDraw(manager, graphical, networkCommunication, positions, drawables, animables, elapsedMs);

        } catch (RegistryManager::ComponentError const &e) {

            (void) e;

            auto tmpAnimables = ComponentsRegistry<comp::Animable>();
            auto &animables = tmpAnimables;

            handleDraw(manager, graphical, networkCommunication, positions, drawables, animables, elapsedMs);

        }

    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        throw ASystem::SystemError("DrawSystem", std::vector<std::string>{"Position", "Drawable"});
    }
}

void DrawSystem::handleDraw(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &nComm, ComponentsRegistry<comp::Position> const &pos, 
    ComponentsRegistry<comp::Drawable> &draw, ComponentsRegistry<comp::Animable> &anim, uint64_t &elapsedMs)
{
    auto controllables = getControllables(manager);
    auto velocities = getVelocities(manager);
    bool viewHasChanged = false;

    for (std::size_t i = 0; i < pos->size(); i++) {

        if (!pos[i] || draw->size() <= i || !draw[i]) {
            continue;
        }

        if (controllables->size() > i && controllables[i]) {
            if (!viewHasChanged) {
                handleView(graphical, nComm, pos[i].value(), controllables[i].value(), viewHasChanged);
            }
            if (controllables[i]->left.second) {
                if (draw[i]->scaleX > 0) {
                    draw[i]->scaleX *= -1;
                }
            } else if (controllables[i]->right.second) {
                if (draw[i]->scaleX < 0) {
                    draw[i]->scaleX *= -1;
                }
            }
        } else {
            if (velocities->size() > i && velocities[i]) {
                if (velocities[i]->negX > 0) {
                    if (draw[i]->scaleX > 0) {
                        draw[i]->scaleX *= -1;
                    }
                } else if (velocities[i]->posX > 0) {
                    if (draw[i]->scaleX < 0) {
                        draw[i]->scaleX *= -1;
                    }
                }
            }
        }


        if (anim->size() > i && anim[i]) {
            graphical->drawSprite(pos[i].value(), draw[i].value(), anim[i].value(), elapsedMs);
        } else {
            graphical->drawSprite(pos[i].value(), draw[i].value());
        }
    }
}

void DrawSystem::handleView(std::shared_ptr<AGraphical> &graphical, std::shared_ptr<ACommunication> &nComm, comp::Position const &pos,
    comp::Controllable const &ctrl, bool &viewHasChanged)
{
    if (nComm && !nComm->isServer()) {
        auto local = nComm->getLocalAddressAndPort();

        if (local.first == ctrl.localAddress && local.second == ctrl.localPort) {
            graphical->setViewCenter(pos);
            viewHasChanged = true;
        }
    } else {
        graphical->setViewCenter(pos);
        viewHasChanged = true;
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

ComponentsRegistry<comp::Velocity> DrawSystem::getVelocities(RegistryManager &manager)
{
    try {
        return manager.getComponents<comp::Velocity>();
    } catch (RegistryManager::ComponentError const &e) {
        (void) e;
        return ComponentsRegistry<comp::Velocity>();
    }
}
