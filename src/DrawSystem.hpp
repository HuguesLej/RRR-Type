/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** DrawSystem
*/

#ifndef DRAWSYSTEM_HPP_
    #define DRAWSYSTEM_HPP_

    #include "ASystem.hpp"

class DrawSystem : public ASystem
{
    public:
        DrawSystem(Registry &registry) : ASystem(registry)
        {
        }
        ~DrawSystem() = default;

        void update(float deltaTime) override
        {
            auto &positions = _registry->getComponents<Position>();
            auto &drawables = _registry->getComponents<Drawable>();

            for (std::size_t i = 0; i < positions.size(); i++) {
                if (positions[i] && drawables[i]) {
                    // Draw the entity
                }
            }
        }
};

#endif /* !DRAWSYSTEM_HPP_ */
