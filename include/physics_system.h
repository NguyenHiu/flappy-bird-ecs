#pragma once

#include <vector>
#include "abstract_system.h"
#include "entity.h"

class PhysicsSystem : public AbstractSystem {
    public:
    PhysicsSystem() {};
    ~PhysicsSystem() {};
    void update(std::vector<Entity*>& entities, float dt);
};