#pragma once

#include <set>
#include "abstract_system.h"
#include "component.h"

class BoxColliderSystem : public AbstractSystem
{
private:
    std::unordered_map<EntityType, std::function<void(Entity *, Entity *)>> m_funcs;
    std::set<EntityType> m_ignoreTypes;

public:
    BoxColliderSystem()
    {
        m_funcs[EntityType::BIRD] = [this](Entity *bird, Entity *other)
        {
            this->processBirdCollider(bird, other);
        };

        m_ignoreTypes.insert(EntityType::BACKGROUND);
    }
    ~BoxColliderSystem() {}
    void update(std::vector<Entity *> &entities, float dt);

private:
    void processBirdCollider(Entity *bird, Entity *other);
    sf::FloatRect getBound(Entity* entity);
};