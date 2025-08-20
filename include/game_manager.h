#pragma once

#include <vector>
#include "abstract_system.h"
#include "entity.h"

class GameManager
{
private:
    std::vector<Entity *> m_entities;
    std::vector<AbstractSystem *> m_systems;

private:
    GameManager() {};
    ~GameManager() {};

public:
    static GameManager &getInstance()
    {
        static GameManager instance;
        return instance;
    }

    void update(float dt);
    void addEntity(Entity* entity);
    void addSystem(AbstractSystem* system);
};