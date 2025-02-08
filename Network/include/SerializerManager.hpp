/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** SerializerManager
*/

#ifndef SERIALIZER_MANAGER_HPP_
    #define SERIALIZER_MANAGER_HPP_

    #include <any>
    #include <cstdint>
    #include <exception>
    #include <functional>
    #include <sstream>
    #include <typeindex>
    #include <unordered_map>
    #include <vector>

class SerializerManager
{
    public:

        class Error : public std::exception
        {
            public:
                enum class Operation {
                    Serialize = 0,
                    Deserialize = 1
                };

                Error(Operation const op, std::string const dataTypeName);
                ~Error() = default;

                const char *what() const noexcept override;

            private:
                std::string _msg;
        };

        SerializerManager() = delete;
        ~SerializerManager() = delete;

        static void registerSerializer(const std::type_index type, std::function<std::vector<uint8_t>(const std::any &)> serialize,
            std::function<std::any(const std::vector<uint8_t> &)> deserialize);

        static std::vector<uint8_t> serialize(const std::any &data);
        static std::any deserialize(const std::vector<uint8_t> &data);

    private:
        static std::unordered_map<std::type_index,
            std::pair<std::function<std::vector<uint8_t>(const std::any &)>, std::function<std::any(const std::vector<uint8_t> &)>>> _serializers;
};

#endif /* !SERIALIZER_MANAGER_HPP_ */
