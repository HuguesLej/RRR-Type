/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** Timer
*/

#include "Timer.hpp"

void Timer::start()
{
    _start = std::chrono::steady_clock::now();
    _end = _start;
    isRunning = true;
}

void Timer::stop()
{
    _end = std::chrono::steady_clock::now();
    isRunning = false;
}

void Timer::reset()
{
    _start = std::chrono::steady_clock::now();
    _end = _start;
}

uint64_t Timer::getElapsedTimeMs()
{
    if (isRunning) {
        _end = std::chrono::steady_clock::now();
    }

    return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count());
}
