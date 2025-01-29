/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** SparseArray
*/

#ifndef SPARSEARRAY_HPP_
    #define SPARSEARRAY_HPP_

    #include <optional>
    #include <vector>

template <typename Component>
using SparseArray = std::vector<std::optional<Component>>;

#endif /* !SPARSEARRAY_HPP_ */
