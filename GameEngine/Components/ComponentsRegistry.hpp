/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** ComponentsRegistry
*/

#ifndef COMPONENTS_REGISTRY_HPP_
    #define COMPONENTS_REGISTRY_HPP_

    #include <optional>
    #include <vector>

template <typename Component>
using ComponentsRegistry = std::vector<std::optional<Component>>;

#endif /* !COMPONENTS_REGISTRY_HPP_ */
