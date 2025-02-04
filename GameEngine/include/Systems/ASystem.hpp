/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** ASystem
*/

#ifndef ASYSTEM_HPP_
    #define ASYSTEM_HPP_

    #include <exception>
    #include <memory>

    #include "Components.hpp"
    #include "AGraphical.hpp"

class RegistryManager;

class ASystem
{
    public:

        class SystemError : public std::exception
        {
            public:
                SystemError(const std::string systemName, const std::vector<std::string> componentsName);
                ~SystemError() = default;

                const char *what() const noexcept override;

            private:
                std::string _msg;
        };

        virtual ~ASystem() = default;

        virtual void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, uint64_t elapsedMs) = 0;
};

#endif /* !ASYSTEM_HPP_ */
