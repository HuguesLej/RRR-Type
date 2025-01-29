/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
    #define REGISTRY_HPP_

    #include <any>
    #include <functional>
    #include <typeindex>
    #include <unordered_map>
    #include "Entity.hpp"
    #include "SparseArray.hpp"

class Registry
{
    public:
        Registry() = default;
        ~Registry() = default;


        template <typename Component>
        SparseArray<Component> &registerComponent()
        {
            auto type = std::type_index(typeid(Component));

            if (_componentsArray.find(type) == _componentsArray.end()) {
                _componentsArray[type] = SparseArray<Component>();

                _eraseFunctions[type] = [](Registry &registry, Entity const &entity) {
                    auto &array = registry.getComponents<Component>();
                    array[entity] = std::nullopt;
                };
            }

            return std::any_cast<SparseArray<Component> &>(_componentsArray[type]);
        }


        template <typename Component>
        SparseArray<Component> &getComponents()
        {
            auto type = std::type_index(typeid(Component));

            if (_componentsArray.find(type) == _componentsArray.end()) {
                _componentsArray[type] = SparseArray<Component>();
            }

            return std::any_cast<SparseArray<Component> &>(_componentsArray[type]);
        }


        template <typename Component>
        SparseArray<Component> const &getComponents() const
        {
            auto type = std::type_index(typeid(Component));

            return std::any_cast<SparseArray<Component> const &>(_componentsArray.find(type)->second);
        }


        Entity spawnEntity()
        {
            return _nextEntity++;
        }


        void killEntity(Entity const &entity)
        {
            for (auto &[type, array] : _componentsArray) {
                _eraseFunctions[type](*this, entity);
            }
        }


        template <typename Component>
        std::optional<Component> addComponent(Entity const &to, Component &&c)
        {
            auto &array = getComponents<Component>();

            if (array.size() <= to) {
                array.resize(to + 1);
            }
            array[to] = std::move(c);

            return array[to].value();
        }


        template <typename Component, typename... Params>
        std::optional<Component> emplaceComponent(Entity const &to, Params &&...p)
        {
            auto &array = getComponents<Component>();

            if (array.size() <= to) {
                array.resize(to + 1);
            }
            array[to] = Component(std::forward<Params>(p)...);

            return array[to].value();
        }


        template <typename Component>
        void removeComponent(Entity const &from)
        {
            auto &array = getComponents<Component>();

            if (from < array.size()) {
                array[from] = std::nullopt;
            }
        }


    private:
        Entity _nextEntity = 0;
        std::unordered_map<std::type_index, std::any> _componentsArray;
        std::unordered_map<std::type_index, std::function<void (Registry &, Entity const &)>> _eraseFunctions;
};

#endif /* !REGISTRY_HPP_ */

