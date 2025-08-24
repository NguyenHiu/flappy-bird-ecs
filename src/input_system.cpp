#include "input_system.h"
#include "logger.h"

InputSystem::InputSystem(KeyMap *keyMap)
{
    if (keyMap != nullptr)
    {
        m_keymap = keyMap;
    }
    else
    {
        m_keymap = new KeyMap();
    }
}

void InputSystem::update(std::vector<Entity *> &entities, float dt)
{
    for (auto *entity : entities)
    {
        if (entity->hasComponent<InputComponent>())
        {
            InputComponent *comp = entity->getComponent<InputComponent>();

            switch (comp->entityType)
            {
            case EntityType::PLAYER:
                this->processPlayerInfo(entity, comp);
                break;

            default:
                Logger::Warn("[Input System] Invalid entity type,", static_cast<int>(comp->entityType));
                break;
            }
        }
    }
}

void InputSystem::processPlayerInfo(Entity *entity, InputComponent *comp)
{
    for (GameAction action : comp->listendedActions)
    {
        if (m_keymap->isActionPressed(action))
        {
            switch (action)
            {
            case GameAction::JUMP:
            {
                PhysicComponent *comp_phy = entity->getComponent<PhysicComponent>();
                // Check jump timer
                if (comp_phy->jumpTimer <= 0)
                {
                    // Valid jump
                    entity->getComponent<VelocityComponent>()->dy = comp_phy->jumpForce;
                    comp_phy->jumpTimer = comp_phy->jumpCooldown;
                    Logger::Info("Jumping...");
                }
                // else
                // {
                //     Logger::Info("Waiting for the cooldown...");
                // }
                break;
            }

            default:
            {
                Logger::Warn("[Input System] Invalid player action,", static_cast<int>(action));
                break;
            }
            }
        }
    }
}