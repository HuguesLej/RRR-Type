/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** AGraphical
*/

#include "AGraphical.hpp"

bool AGraphical::isKeyPressed(Keys key)
{
    if (key == Keys::None) {
        return false;
    }
    return _keysState[key];
}
