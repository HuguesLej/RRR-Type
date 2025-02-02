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
    #include "../Graphicals/IGraphical.hpp"

class RegistryManager;

class ASystem
{
    public:
        virtual ~ASystem() = default;

        virtual void update(RegistryManager &manager, std::shared_ptr<IGraphical> &graphical, float elapsedSeconds) = 0;
};

#endif /* !ASYSTEM_HPP_ */
