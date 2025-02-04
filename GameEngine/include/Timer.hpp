/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** Timer
*/

#ifndef TIMER_HPP_
    #define TIMER_HPP_

    #include <chrono>

class Timer
{
    public:
        Timer() = default;
        ~Timer() = default;

        void start();
        void stop();
        void reset();
        uint64_t getElapsedTimeMs();

    private:
        std::chrono::time_point<std::chrono::steady_clock> _start;
        std::chrono::time_point<std::chrono::steady_clock> _end;
        bool isRunning;
};

#endif /* !TIMER_HPP_ */
