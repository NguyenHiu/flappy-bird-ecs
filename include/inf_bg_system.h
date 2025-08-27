#pragma once

#include "abstract_system.h"

class InfBgSystem : public AbstractSystem
{
public:
    InfBgSystem() {}
    ~InfBgSystem() {}
    void update(std::vector<Entity *> &entities, float dt);
};