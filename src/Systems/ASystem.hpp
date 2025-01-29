/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** ASystem
*/

#ifndef ASYSTEM_HPP_
    #define ASYSTEM_HPP_

    #include <memory>
    #include "../Components/Components.hpp"
    #include "../Registry.hpp"

class ASystem
{
    public:
        ASystem(std::shared_ptr<Registry> &registry) : _registry(registry)
        {
        }
        virtual ~ASystem() = default;

        virtual void update(float deltaTime) = 0;

    protected:
        std::shared_ptr<Registry> _registry;
};

#endif /* !ASYSTEM_HPP_ */
