/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** DrawSystem
*/

#ifndef DRAWSYSTEM_HPP_
    #define DRAWSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "../RegistryManager.hpp"

class DrawSystem : public ASystem
{
    public:
        DrawSystem() = default;
        ~DrawSystem() = default;

        void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, float elapsedMs) override
        {
            (void) elapsedMs;

            try {

                auto &positions = manager.getComponents<comp::Position>();
                auto &drawables = manager.getComponents<comp::Drawable>();

                try {

                    auto &animables = manager.getComponents<comp::Animable>();

                    for (std::size_t i = 0; i < positions.size(); i++) {

                        if (!positions[i] || drawables.size() <= i || !drawables[i]) {
                            continue;
                        }

                        if (animables.size() > i && animables[i]) {
                            graphical->drawSprite(positions[i].value(), drawables[i].value(), animables[i].value());
                        } else {
                            graphical->drawSprite(positions[i].value(), drawables[i].value());
                        }
                    }

                } catch (RegistryManager::ComponentError const &e) {

                    (void) e;

                    for (std::size_t i = 0; i < positions.size(); i++) {

                        if (!positions[i] || drawables.size() <= i || !drawables[i]) {
                            continue;
                        }

                        graphical->drawSprite(positions[i].value(), drawables[i].value());
                    }

                }

            } catch (RegistryManager::ComponentError const &e) {
                (void) e;
                throw ASystem::SystemError("DrawSystem", std::vector<std::string>{"Position", "Drawable"});
            }
        }
};

#endif /* !DRAWSYSTEM_HPP_ */
