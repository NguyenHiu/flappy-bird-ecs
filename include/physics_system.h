#pragma once

#include <vector>
#include "abstract_system.h"
#include "entity.h"

class PhysicsSystem : public AbstractSystem
{
private:
    float m_gravity;

public:
    PhysicsSystem(float gravity) : m_gravity(gravity) {};
    ~PhysicsSystem() {};
    void update(std::vector<Entity *> &entities, float dt);
};