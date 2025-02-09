/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** RegistryManager
*/

#ifndef REGISTRY_MANAGER_HPP_
    #define REGISTRY_MANAGER_HPP_

    #include <algorithm>
    #include <any>
    #include <exception>
    #include <functional>
    #include <memory>
    #include <typeindex>
    #include <unordered_map>

    #include "Entity.hpp"
    #include "ComponentsRegistry.hpp"
    #include "ASystem.hpp"
    #include "SystemsRegistry.hpp"
    #include "AGraphical.hpp"
    #include "ACommunication.hpp"

class ASystem;

class RegistryManager
{
    public:

        class SystemError : public std::exception
        {
            public:
                SystemError(std::string const &systemType);
                ~SystemError() = default;

                const char *what() const noexcept override;

            private:
                std::string _msg;
        };


        class ComponentError : public std::exception
        {
            public:

                enum Type
                {
                    NOT_REGISTERED = 0,
                    ALREADY_REGISTERED = 1
                };

                ComponentError(Type type, std::string const &componentType);
                ~ComponentError() = default;

                const char *what() const noexcept override;

            private:
                std::string _msg;
        };


        RegistryManager(std::shared_ptr<AGraphical> graphical = nullptr, std::shared_ptr<ACommunication> networkCommunication = nullptr);
        RegistryManager(std::shared_ptr<AGraphical> graphical);
        RegistryManager(std::shared_ptr<ACommunication> networkCommunication);
        ~RegistryManager() = default;

        Entity spawnEntity();
        void killEntity(Entity const &entity);

        void addSystem(std::unique_ptr<ASystem> system);
        void updateSystems(uint64_t elapsedMs);

        const std::unordered_map<std::type_index, std::any> &getComponentsRegistries() const;
        void replaceComponent(std::any registry);


        template <typename Component>
        ComponentsRegistry<Component> &registerComponent()
        {
            auto type = std::type_index(typeid(ComponentsRegistry<Component>));

            if (_componentsRegistriesMap.find(type) != _componentsRegistriesMap.end()) {
                throw ComponentError(ComponentError::ALREADY_REGISTERED, typeid(Component).name());
            }

            _componentsRegistriesMap[type] = ComponentsRegistry<Component>();
            _eraseFunctions[type] = [](RegistryManager &manager, Entity const &entity) {
                auto &array = manager.getComponents<Component>();
                array[entity] = std::nullopt;
            };

            return std::any_cast<ComponentsRegistry<Component> &>(_componentsRegistriesMap[type]);
        }


        template <typename Component>
        ComponentsRegistry<Component> &getComponents()
        {
            auto type = std::type_index(typeid(ComponentsRegistry<Component>));

            if (_componentsRegistriesMap.find(type) == _componentsRegistriesMap.end()) {
                throw ComponentError(ComponentError::NOT_REGISTERED, typeid(Component).name());
            }

            return std::any_cast<ComponentsRegistry<Component> &>(_componentsRegistriesMap[type]);
        }


        template <typename Component>
        std::optional<Component> addComponent(Entity const &to, Component &&c)
        {
            auto &array = getComponents<Component>();

            if (to >= array->size()) {
                array->resize(to + 1);
            }
            array[to] = std::move(c);
            return array[to].value();
        }


        template <typename Component, typename... Params>
        std::optional<Component> emplaceComponent(Entity const &to, Params &&...p)
        {
            auto &array = getComponents<Component>();

            if (to >= array->size()) {
                array->resize(to + 1);
            }
            array[to] = Component(std::forward<Params>(p)...);
            return array[to].value();
        }


        template <typename Component>
        void removeComponent(Entity const &from)
        {
            auto &array = getComponents<Component>();

            if (from < array->size()) {
                array[from] = std::nullopt;
            }
        }


    private:
        Entity _nextEntity = 0;

        std::unordered_map<std::type_index, std::any> _componentsRegistriesMap;
        std::unordered_map<std::type_index, std::function<void (RegistryManager &, Entity const &)>> _eraseFunctions;

        SystemsRegistry _systems;

        std::shared_ptr<AGraphical> _graphical;
        std::shared_ptr<ACommunication> _networkCommunication;
};

#endif /* !REGISTRY_MANAGER_HPP_ */
