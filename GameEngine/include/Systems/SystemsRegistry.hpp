/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** SystemsRegistry
*/

#ifndef SYSTEMS_REGISTRY_HPP_
    #define SYSTEMS_REGISTRY_HPP_

    #include <memory>
    #include <vector>

    #include "ASystem.hpp"

using SystemsRegistry = std::vector<std::unique_ptr<ASystem>>;

#endif /* !SYSTEMS_REGISTRY_HPP_ */
