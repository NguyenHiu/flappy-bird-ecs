#pragma once

#include <vector>
#include "abstract_system.h"
#include "entity.h"
#include "game_manager.h"

class PhysicsSystem : public AbstractSystem
{
private:
    float m_gravity;
    GameManager& m_gMgr = GameManager::getInstance();

public:
    PhysicsSystem(float gravity) : m_gravity(gravity) {};
    ~PhysicsSystem() {};
    void update(std::vector<Entity *> &entities, float dt);

private:
    void processBirdRotate(Entity *entity, float vy, float maxYSpeed);
    void updateIdleState(std::vector<Entity *> &entities, float dt);
    void processBirdIdle(Entity* entity);
    void processGroundIdle(Entity* entity, float dt);
    void updateRunState(std::vector<Entity *> &entities, float dt);
    void processEntityRun(Entity* entity, float dt);
};