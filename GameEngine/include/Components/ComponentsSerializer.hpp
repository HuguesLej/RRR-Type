/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** ComponentsSerializer
*/

#ifndef COMPONENTS_SERIALIZER_HPP_
    #define COMPONENTS_SERIALIZER_HPP_

    #include <any>
    #include <exception>
    #include <sstream>
    #include <typeindex>
    #include <unordered_map>

    #include "Components.hpp"
    #include "ComponentsRegistry.hpp"
    #include "SerializerManager.hpp"

class ComponentsSerializer
{
    public:

        class Error : public std::exception
        {
            public:
                enum Type {
                    SERIALIZE = 0,
                    DESERIALIZE = 1
                };

                Error(Type type);
                ~Error() = default;

                const char *what() const noexcept override;

            private:
                std::string _msg;
        };

        ComponentsSerializer() = delete;
        ~ComponentsSerializer() = delete;

        static void registerSerializers();

    private:
        template <typename Component>
        static std::vector<uint8_t> serializeRegistry(const std::any &data)
        {
            try {
                ComponentsRegistry<Component> registry = std::any_cast<ComponentsRegistry<Component>>(data);
                std::ostringstream oss;

                for (auto &component : registry) {
                    if (component.has_value()) {
                        oss << "1 ";
                        serializeComponent(oss, *component);
                    } else {
                        oss << "0 ";
                    }
                }

                std::string ossStr = oss.str();
                std::vector<uint8_t> serializedData(ossStr.begin(), ossStr.end());

                return serializedData;
            } catch (const std::bad_any_cast &e) {
                (void) e;
                throw Error(Error::SERIALIZE);
            }
        }

        template <typename Component>
        static std::any deserializeRegistry(const std::vector<uint8_t> &data)
        {
            try {
                std::istringstream iss(std::string(data.begin(), data.end()));
                ComponentsRegistry<Component> registry;
                std::string hasValue;

                while (iss >> hasValue) {
                    if (hasValue == "1") {
                        Component component;
                        deserializeComponent(iss, component);
                        registry.push_back(component);
                    } else {
                        registry.push_back(std::nullopt);
                    }
                }

                return std::make_any<ComponentsRegistry<Component>>(registry);
            } catch (const std::bad_any_cast &e) {
                (void) e;
                throw Error(Error::DESERIALIZE);
            }
        }

        template <typename Component>
        static void registerComponent()
        {
            SerializerManager::registerSerializer(
                std::type_index(typeid(ComponentsRegistry<Component>)),
                serializeRegistry<Component>,
                deserializeRegistry<Component>
            );
        }


        static void serializeComponent(std::ostringstream &oss, const comp::Position &component);
        static void deserializeComponent(std::istringstream &iss, comp::Position &component);

        static void serializeComponent(std::ostringstream &oss, const comp::Velocity &component);
        static void deserializeComponent(std::istringstream &iss, comp::Velocity &component);

        static void serializeComponent(std::ostringstream &oss, const comp::Drawable &component);
        static void deserializeComponent(std::istringstream &iss, comp::Drawable &component);

        static void serializeComponent(std::ostringstream &oss, const comp::Animable &component);
        static void deserializeComponent(std::istringstream &iss, comp::Animable &component);

        static void serializeComponent(std::ostringstream &oss, const comp::Controllable &component);
        static void deserializeComponent(std::istringstream &iss, comp::Controllable &component);

        static void serializeComponent(std::ostringstream &oss, const comp::Collider &component);
        static void deserializeComponent(std::istringstream &iss, comp::Collider &component);

        static void serializeComponent(std::ostringstream &oss, const comp::Gravity &component);
        static void deserializeComponent(std::istringstream &iss, comp::Gravity &component);

        static void serializeComponent(std::ostringstream &oss, const comp::Jumpable &component);
        static void deserializeComponent(std::istringstream &iss, comp::Jumpable &component);

        static void serializeComponent(std::ostringstream &oss, const comp::Health &component);
        static void deserializeComponent(std::istringstream &iss, comp::Health &component);
};

#endif /* !COMPONENTS_SERIALIZER_HPP_ */
