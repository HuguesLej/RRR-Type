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

        void update(RegistryManager &manager, float deltaTime) override
        {
            auto &positions = manager.getComponents<comp::Position>();
            auto &drawables = manager.getComponents<comp::Drawable>();

            for (std::size_t i = 0; i < positions.size(); i++) {
                if (positions[i] && drawables[i]) {
                    // Draw the entity
                }
            }
        }
};

#endif /* !DRAWSYSTEM_HPP_ */
