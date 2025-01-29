/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** ASystem
*/

#ifndef ASYSTEM_HPP_
    #define ASYSTEM_HPP_

    #include <memory>
    #include "Components.hpp"
    #include "Registry.hpp"

class ASystem
{
    public:
        ASystem(Registry &registry)
        {
            _registry = std::make_shared<Registry>(registry);
        }
        virtual ~ASystem() = default;

        virtual void update(float deltaTime) = 0;

    protected:
        std::shared_ptr<Registry> _registry;
};

#endif /* !ASYSTEM_HPP_ */
