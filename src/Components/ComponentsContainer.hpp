/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** ComponentsContainer
*/

#ifndef COMPONENTS_CONTAINER_HPP_
    #define COMPONENTS_CONTAINER_HPP_

    #include <optional>
    #include <vector>

template <typename Component>
using ComponentsContainer = std::vector<std::optional<Component>>;

#endif /* !COMPONENTS_CONTAINER_HPP_ */
