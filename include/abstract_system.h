#pragma once

#include <vector>
#include "entity.h"

class AbstractSystem {
    public:
        virtual void update(std::vector<Entity*>& entities, float deltaTime) = 0;
};