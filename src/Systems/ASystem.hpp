/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** ASystem
*/

#ifndef ASYSTEM_HPP_
    #define ASYSTEM_HPP_

    #include "../Components/Components.hpp"

class Registry;

class ASystem
{
    public:
        virtual ~ASystem() = default;

        virtual void update(Registry &registry, float deltaTime) = 0;
};

#endif /* !ASYSTEM_HPP_ */
