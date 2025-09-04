#include <math.h>
#include "physics_system.h"
#include "component.h"
#include "logger.h"

void PhysicsSystem::update(std::vector<Entity *> &entities, float dt)
{
    switch (m_gMgr.getGameState())
    {
    case GameState::IDLE:
        this->updateIdleState(entities, dt);
        break;
    case GameState::RUN:
        this->updateRunState(entities, dt);
        break;
    case GameState::IS_ENDING:
        this->updateEndState(entities, dt);
        break;
    case GameState::END:
        break;

    default:
        Logger::Warn("Detect anomaly game state, O` E' O` E'");
        break;
    }
}

void PhysicsSystem::processBirdRotate(Entity *entity, float vy, float maxYSpeed)
{
    BirdRotateComponent *comp = entity->getComponent<BirdRotateComponent>();
    float angle = comp->defaultAngle;
    if (vy > comp->threshold)
    {
        // Calculate the angle between the maximum velocity (the jump force) and the current one
        float angleRadians = std::asin(vy / maxYSpeed);
        angle = angleRadians / M_PI * 180.f;
    }
    if (entity->hasComponent<SpriteComponent>())
        entity->getComponent<SpriteComponent>()->spriteData.rotationDegree = angle;
    if (entity->hasComponent<HSpritesheetComponent>())
        entity->getComponent<HSpritesheetComponent>()->spriteData.rotationDegree = angle;
}

// Perform Game at Idle State
// The bird is flying up-down around the center of the screen
// The ground is running
// THe pipe is idling (on the right of the screen, waiting for the game start)
void PhysicsSystem::updateIdleState(std::vector<Entity *> &entities, float dt)
{
    for (auto *entity : entities)
    {
        switch (entity->getType())
        {
        case EntityType::BIRD:
            this->processBirdIdle(entity);
            break;
        case EntityType::GROUND:
            this->processEntityRun(entity, dt);
        default:
            break;
        }
    }
}

void PhysicsSystem::processBirdIdle(Entity *entity)
{
    // TODO: up-down
}

void PhysicsSystem::updateRunState(std::vector<Entity *> &entities, float dt)
{
    // Logger::Debug("Run State updating...");
    for (auto *entity : entities)
    {
        this->processEntityRun(entity, dt);
    }
}

void PhysicsSystem::updateEndState(std::vector<Entity *> &entities, float dt)
{
    // Process bird only - make it fall
    for (auto* entity : entities)
    {
        if (entity->getType() == EntityType::BIRD)
        {
            this->processEntityRun(entity, dt);
        }
    }
}

void PhysicsSystem::processEntityRun(Entity *entity, float dt)
{
    auto *pos = entity->getComponent<PositionComponent>();
    auto *vel = entity->getComponent<VelocityComponent>();
    auto *phy = entity->getComponent<PhysicComponent>();

    if (!pos || !vel || !phy)
    {
        // Logger::Debug("Entity", entity->getId(), "doesn't have enough components to perform physic");
        return;
    }

    // Accumulate jump timer
    phy->jumpTimer -= dt;

    // Apply gravity
    if (phy && phy->hasGravity && !phy->onGround)
    {
        vel->dy += m_gravity * phy->gravityScale * dt;
        // Logger::Debug("apply gravity, Vy:", vel->dy);
    }

    // Clamp velocity
    vel->dx = std::clamp(vel->dx, -vel->maxSpeed, vel->maxSpeed);
    vel->dy = std::clamp(vel->dy, -vel->maxSpeed, vel->maxSpeed);

    // Apply velocity   
    pos->x += vel->dx * dt;
    pos->y += vel->dy * dt;

    // Rotate the bird =D
    if (entity->hasComponent<BirdRotateComponent>())
    {
        this->processBirdRotate(entity, vel->dy, vel->maxSpeed);
    }
}