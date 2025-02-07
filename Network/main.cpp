/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** main
*/

#include <iostream>
#include "SerializerManager.hpp"

struct Position
{
    float x;
    float y;

    Position(float x = 0, float y = 0) : x(x), y(y) {}
};

std::vector<uint8_t> serializeString(const std::any &data)
{
    std::string str = std::any_cast<std::string>(data);
    std::vector<uint8_t> serializedData(str.begin(), str.end());

    return serializedData;
}

std::any deserializeString(const std::vector<uint8_t> &data)
{
    std::string str(data.begin(), data.end());

    return std::make_any<std::string>(str);
}

std::vector<uint8_t> serializePosition(const std::any &data)
{
    const Position pos = std::any_cast<Position>(data);
    std::ostringstream oss;

    oss << pos.x << ' ' << pos.y << ' ';

    std::string ossStr = oss.str();
    std::vector<uint8_t> serializedData(ossStr.begin(), ossStr.end());

    return serializedData;
}

std::any deserializePosition(const std::vector<uint8_t> &data)
{
    std::istringstream iss(std::string(data.begin(), data.end()));
    Position pos;

    iss >> pos.x;
    iss >> pos.y;

    auto tmp = std::make_any<Position>(pos);
    return tmp;
}

int main(void)
{
    SerializerManager::registerSerializer(std::type_index(typeid(std::string)), serializeString, deserializeString);
    SerializerManager::registerSerializer(std::type_index(typeid(Position)), serializePosition, deserializePosition);

    std::string startStr = "Hello World!";
    std::vector<uint8_t> serializedStr = SerializerManager::serialize(std::make_any<std::string>(startStr));
    std::any deserializedStr = SerializerManager::deserialize(serializedStr);
    std::string endStr = std::any_cast<std::string>(deserializedStr);

    std::cout << "Start: " << startStr << std::endl;
    std::cout << "End: " << endStr << std::endl;

    Position startPos(10, 20);
    std::vector<uint8_t> serializedPos = SerializerManager::serialize(std::make_any<Position>(startPos));
    std::any deserializedPos = SerializerManager::deserialize(serializedPos);

    Position endPos = std::any_cast<Position>(deserializedPos);

    std::cout << "Start: " << startPos.x << ", " << startPos.y << std::endl;
    std::cout << "End: " << endPos.x << ", " << endPos.y << std::endl;

    return 0;
}
