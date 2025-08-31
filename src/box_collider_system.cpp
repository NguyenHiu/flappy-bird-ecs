#include "box_collider_system.h"
#include "util.h"
#include "logger.h"
#include "game_manager.h"

void BoxColliderSystem::update(std::vector<Entity *> &entities, float dt)
{
    for (auto *entity : entities)
    {
        // Skip if the entity doesn't have Box Collider
        if (!entity->hasComponent<BoxColliderComponent>())
            continue;

        BoxColliderComponent *entityBox = entity->getComponent<BoxColliderComponent>();
        auto it = m_funcs.find(entityBox->tag);
        // Skip if there is no setup logic for the collision
        if (it == m_funcs.end())
            continue;
        for (auto *other : entities)
        {
            // Skip the same entity
            if (other->getId() == entity->getId())
                continue;

            // Only process if `other` entity also has Box Collider Component
            if (!other->hasComponent<BoxColliderComponent>())
                continue;

            BoxColliderComponent *otherBox = other->getComponent<BoxColliderComponent>();

            // Check if they are collided
            // Logger::Debug("entity", entityBox->rect.position.x, entityBox->rect.position.y, entityBox->rect.size.x, entityBox->rect.size.y);
            // Logger::Debug("entity", otherBox->rect.position.x, otherBox->rect.position.y, otherBox->rect.size.x, otherBox->rect.size.y);
            if (Utils::isOverlapping(entityBox->rect, otherBox->rect))
            {
                // Logger::Debug("is overlapping...");
                // Process if valid
                it->second(entity, other);
            }
        }
    }
}

void BoxColliderSystem::processBirdCollider(Entity *bird, Entity *other)
{
    if (!other->hasComponent<BoxColliderComponent>())
        return;

    BoxColliderComponent *comp = other->getComponent<BoxColliderComponent>();
    switch (comp->tag)
    {
    case ColliderTag::Ground:
    {
        GameManager::getInstance().endGame();
        break;
    }
    default:
        Logger::Warn("Detect anomaly object, O` E' O` E'");
        break;
    }
}