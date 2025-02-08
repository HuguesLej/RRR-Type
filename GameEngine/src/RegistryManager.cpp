/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** RegistryManager
*/

#include "RegistryManager.hpp"


RegistryManager::SystemError::SystemError(std::string const &systemType)
{
    _msg = "System has already been added to the registry: " + systemType;
}

const char *RegistryManager::SystemError::what() const noexcept
{
    return _msg.c_str();
}


RegistryManager::ComponentError::ComponentError(Type type, std::string const &componentType)
{
    if (type == ALREADY_REGISTERED) {
        _msg = "Component type has already been registered: " + componentType;
    } else {
        _msg = "Component type has not been registered: " + componentType;
    }
}

const char *RegistryManager::ComponentError::what() const noexcept
{
    return _msg.c_str();
}


RegistryManager::RegistryManager(std::shared_ptr<AGraphical> graphical, std::shared_ptr<ACommunication> networkCommunication) : _graphical(graphical), _networkCommunication(networkCommunication)
{
}

RegistryManager::RegistryManager(std::shared_ptr<AGraphical> graphical) : _graphical(graphical), _networkCommunication(nullptr)
{
}

RegistryManager::RegistryManager(std::shared_ptr<ACommunication> networkCommunication) : _graphical(nullptr), _networkCommunication(networkCommunication)
{
}


Entity RegistryManager::spawnEntity()
{
    return _nextEntity++;
}

void RegistryManager::killEntity(Entity const &entity)
{
    for (auto &[type, _] : _componentsRegistriesMap) {
        _eraseFunctions[type](*this, entity);
    }
}


void RegistryManager::addSystem(std::unique_ptr<ASystem> system)
{
    auto it = std::find_if(_systems.begin(), _systems.end(), [&system] (const auto &existingSystem) {
        return typeid(*existingSystem) == typeid(*system);
    });

    if (it != _systems.end()) {
        throw SystemError(typeid(*system).name());
    }

    _systems.push_back(std::move(system));
}


void RegistryManager::updateSystems(uint64_t elapsedMs)
{
    for (auto &system : _systems) {
        system->update(*this, _graphical, elapsedMs);
    }
}


const std::unordered_map<std::type_index, std::any> &RegistryManager::getComponentsRegistries() const
{
    return _componentsRegistriesMap;
}

void RegistryManager::replaceComponent(ComponentsRegistry<std::any> registry)
{
    for (auto &component : registry) {
        if (!component.has_value()) {
            continue;
        }

        auto type = std::type_index(component.type());

        if (_componentsRegistriesMap.find(type) == _componentsRegistriesMap.end()) {
            throw ComponentError(ComponentError::NOT_REGISTERED, component.type().name());
        }

        _componentsRegistriesMap[type] = registry;
        break;
    }
}
