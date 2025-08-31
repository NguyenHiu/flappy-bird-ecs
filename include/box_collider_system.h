#pragma once

#include "abstract_system.h"
#include "component.h"

class BoxColliderSystem : public AbstractSystem
{
private:
    std::unordered_map<ColliderTag, std::function<void(Entity *, Entity *)>> m_funcs;

public:
    BoxColliderSystem()
    {
        m_funcs[ColliderTag::Bird] = [this](Entity *bird, Entity *other)
        {
            this->processBirdCollider(bird, other);
        };
    }
    ~BoxColliderSystem() {}
    void update(std::vector<Entity *> &entities, float dt);

private:
    void processBirdCollider(Entity *bird, Entity *other);
};