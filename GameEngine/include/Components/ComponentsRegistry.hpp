/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** ComponentsRegistry
*/

#ifndef COMPONENTS_REGISTRY_HPP_
    #define COMPONENTS_REGISTRY_HPP_

    #include <optional>
    #include <vector>

template <typename Component>
class ComponentsRegistry {
    public:
        ComponentsRegistry(bool sendOnce = false) : _sendOnce(sendOnce)
        {
        }
        ~ComponentsRegistry() = default;


        bool sendOnce()
        {
            return _sendOnce;
        }

        bool sendOnce() const
        {
            return _sendOnce;
        }

        void sendOnce(bool sendOnce)
        {
            _sendOnce = sendOnce;
        }


        bool sent()
        {
            return _sent;
        }

        bool sent() const
        {
            return _sent;
        }

        void sent(bool sent)
        {
            _sent = sent;
        }


        std::vector<std::optional<Component>>* operator->()
        {
            return &_components;
        }

        const std::vector<std::optional<Component>>* operator->() const
        {
            return &_components;
        }


        std::vector<std::optional<Component>>& operator*()
        {
            return _components;
        }

        std::vector<std::optional<Component>> const& operator*() const
        {
            return _components;
        }


        std::optional<Component>& operator[](std::size_t index)
        {
            return _components[index];
        }

        std::optional<Component> const& operator[](std::size_t index) const
        {
            return _components[index];
        }


        void operator=(std::vector<std::optional<Component>> components)
        {
            _components = components;
        }

    private:
        std::vector<std::optional<Component>> _components;

        bool _sendOnce;
        bool _sent = false;
};

#endif /* !COMPONENTS_REGISTRY_HPP_ */
