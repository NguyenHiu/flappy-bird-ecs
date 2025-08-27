#include <math.h>
#include "physics_system.h"
#include "component.h"
#include "logger.h"

void PhysicsSystem::update(std::vector<Entity *> &entities, float dt)
{
    for (auto *entity : entities)
    {
        auto *pos = entity->getComponent<PositionComponent>();
        auto *vel = entity->getComponent<VelocityComponent>();
        auto *phy = entity->getComponent<PhysicComponent>();

        if (!pos || !vel || !phy)
        {
            // Logger::Debug("Entity", entity->getId(), "doesn't have enough components to perform physic");
            continue;
        }

        // Accumulate jump timer
        phy->jumpTimer -= dt;

        // Apply gravity
        if (phy && phy->hasGravity && !phy->onGround)
        {
            vel->dy += m_gravity * phy->gravityScale * dt;
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