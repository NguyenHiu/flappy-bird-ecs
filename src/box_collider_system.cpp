#include "box_collider_system.h"
#include "util.h"
#include "logger.h"
#include "game_manager.h"

void BoxColliderSystem::update(std::vector<Entity *> &entities, float dt)
{
    if (GameManager::getInstance().getGameState() == GameState::IDLE)
        return;

    for (auto *entity : entities)
    {
        if (m_ignoreTypes.find(entity->getType()) != m_ignoreTypes.end())
            continue;

        sf::FloatRect entityRect = this->getBound(entity);
        if (entityRect == sf::FloatRect())
            continue;

        auto it = m_funcs.find(entity->getType());
        // Skip if there is no setup logic for the collision
        if (it == m_funcs.end())
            continue;

        for (auto *other : entities)
        {
            // Skip the same entity
            if (other->getId() == entity->getId())
                continue;

            if (m_ignoreTypes.find(other->getType()) != m_ignoreTypes.end())
                continue;

            // Check if they are collided
            sf::FloatRect otherRect = this->getBound(other);
            if (otherRect == sf::FloatRect())
                continue;
            if (Utils::isOverlapping(entityRect, otherRect))
                it->second(entity, other);
        }
    }
}

void BoxColliderSystem::processBirdCollider(Entity *bird, Entity *other)
{
    switch (other->getType())
    {
    case EntityType::GROUND:
    {
        GameManager::getInstance().endGame();
        break;
    }
    case EntityType::PIPE:
    {
        GameManager::getInstance().setIsEndingGame();
        break;
    }
    default:
        Logger::Warn("Detect anomaly object, O` E' O` E'", static_cast<int>(other->getType()));
        break;
    }
}

sf::FloatRect BoxColliderSystem::getBound(Entity *entity)
{
    if (entity->hasComponent<SpriteComponent>())
        return entity->getComponent<SpriteComponent>()->spriteData.sprite.getGlobalBounds();
    else if (entity->hasComponent<HSpritesheetComponent>())
        return entity->getComponent<HSpritesheetComponent>()->spriteData.sprite.getGlobalBounds();
    return sf::FloatRect();
}