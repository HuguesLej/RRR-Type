/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** SerializerManager
*/

#include "SerializerManager.hpp"

std::unordered_map<std::type_index,
    std::pair<std::function<std::vector<uint8_t>(const std::any &)>, std::function<std::any(const std::vector<uint8_t> &)>>> SerializerManager::_serializers;


SerializerManager::Error::Error(Operation const op, std::string const dataTypeName)
{
    _msg = "Unknown component type on ";
    if (op == Operation::Serialize) {
        _msg += "serialize";
    } else {
        _msg += "deserialize";
    }
    _msg += ": " + dataTypeName;
}

const char *SerializerManager::Error::what() const noexcept
{
    return _msg.c_str();
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
        throw Error(Error::Operation::Serialize, data.type().name());
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
        throw Error(Error::Operation::Deserialize, typeName);
    }

    std::vector<uint8_t> serializedData((std::istreambuf_iterator<char>(iss)), std::istreambuf_iterator<char>());

    return deserializer(serializedData);
}
