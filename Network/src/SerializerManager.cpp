/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** SerializerManager
*/

#include "SerializerManager.hpp"

std::unordered_map<std::type_index,
    std::pair<std::function<std::vector<uint8_t>(const std::any &)>, std::function<std::any(const std::vector<uint8_t> &)>>> SerializerManager::_serializers;


const char *SerializerManager::Error::what() const noexcept
{
    return "Unknown component type";
}


void SerializerManager::registerSerializer(const std::type_index type, std::function<std::vector<uint8_t>(const std::any &)> serialize,
    std::function<std::any(const std::vector<uint8_t> &)> deserialize)
{
    _serializers[type] = std::make_pair(serialize, deserialize);
}

std::vector<uint8_t> SerializerManager::serialize(const std::any &data)
{
    auto it = _serializers.find(std::type_index(data.type()));

    if (it == _serializers.end()) {
        throw Error();
    }

    std::string typeName = data.type().name() + std::string(" ");
    std::vector<uint8_t> serializedData = it->second.first(data);

    serializedData.insert(serializedData.begin(), typeName.begin(), typeName.end());
    return serializedData;
}

std::any SerializerManager::deserialize(const std::vector<uint8_t> &data)
{
    std::function<std::any(const std::vector<uint8_t> &)> deserializer = nullptr;
    std::istringstream iss(std::string(data.begin(), data.end()));
    std::string typeName;

    iss >> typeName;

    for (auto &it : _serializers) {
        if (it.first.name() == typeName) {
            deserializer = it.second.second;
            break;
        }
    }

    if (!deserializer) {
        throw Error();
    }

    std::vector<uint8_t> serializedData((std::istreambuf_iterator<char>(iss)), std::istreambuf_iterator<char>());

    return deserializer(serializedData);
}
