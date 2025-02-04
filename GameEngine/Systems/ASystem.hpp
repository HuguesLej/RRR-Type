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
    #include "../Components/Components.hpp"
    #include "../Graphicals/AGraphical.hpp"

class RegistryManager;

class ASystem
{
    public:

        class SystemError : public std::exception
        {
            public:
                SystemError(const std::string systemName, const std::vector<std::string> componentsName)
                {
                    _msg = systemName + " needs the following components: ";

                    for (size_t i = 0; i < componentsName.size() - 1; i++) {
                        _msg += componentsName[i];

                        if (i < componentsName.size() - 2) {
                            _msg += ", ";
                        }
                    }
                }
                const char *what() const noexcept override {
                    return _msg.c_str();
                }

            private:
                std::string _msg;
        };

        virtual ~ASystem() = default;

        virtual void update(RegistryManager &manager, std::shared_ptr<AGraphical> &graphical, float elapsedMs) = 0;
};

#endif /* !ASYSTEM_HPP_ */
