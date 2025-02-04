/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** ASystem
*/

#include "ASystem.hpp"

ASystem::SystemError::SystemError(const std::string systemName, const std::vector<std::string> componentsName)
{
    _msg = systemName + " needs the following components: ";

    for (size_t i = 0; i < componentsName.size() - 1; i++) {
        _msg += componentsName[i];

        if (i < componentsName.size() - 2) {
            _msg += ", ";
        }
    }
}

const char *ASystem::SystemError::what() const noexcept {
    return _msg.c_str();
}
