#pragma once

#include "abstract_system.h"
#include "component.h"
#include "key_map.h"
#include "entity.h"

class InputSystem : public AbstractSystem
{
    private:
    KeyMap* m_keymap;
public:
    InputSystem(KeyMap* keyMap);
    ~InputSystem() {}
    void update(std::vector<Entity *> &entities, float dt);

private:
    void processPlayerInfo(Entity *entity, InputComponent *comp);
};