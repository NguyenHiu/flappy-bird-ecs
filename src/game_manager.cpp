#include "game_manager.h"
#include "logger.h"

void GameManager::update(float dt)
{
    for (auto *system : m_systems)
    {
        system->update(m_entities, dt);
    }
    // Logger::Debug("Complete game update");
}

void GameManager::addEntity(Entity* entity) {
    m_entities.push_back(entity);
}

void GameManager::addSystem(AbstractSystem* system) {
    m_systems.push_back(system);
}