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

        void start()
        {
            _start = std::chrono::steady_clock::now();
            _end = _start;
            isRunning = true;
        }

        void stop()
        {
            _end = std::chrono::steady_clock::now();
            isRunning = false;
        }

        void reset()
        {
            _start = std::chrono::steady_clock::now();
            _end = _start;
        }

        uint64_t getElapsedTimeMs()
        {
            if (isRunning) {
                _end = std::chrono::steady_clock::now();
            }

            return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count());
        }

    private:
        std::chrono::time_point<std::chrono::steady_clock> _start;
        std::chrono::time_point<std::chrono::steady_clock> _end;
        bool isRunning;
};

#endif /* !TIMER_HPP_ */
