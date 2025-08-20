#include "physics_system.h"
#include "component.h"

void PhysicsSystem::update(std::vector<Entity*>& entities, float dt) {
    for (auto* entity : entities) {
        auto* pos = entity->getComponent<PositionComponent>();
        auto* vel = entity->getComponent<VelocityComponent>();
        auto* phy = entity->getComponent<PhysicComponent>();

        // apply gravity
        if (phy && phy->hasGravity && !phy->onGround) {
            vel->dy -= 800.0f * phy->gravityScale * dt;
        }

        // clamp velocity
        if (vel->dx > vel->maxSpeed) vel->dx = vel->maxSpeed;
        if (vel->dx < -vel->maxSpeed) vel->dx = -vel->maxSpeed;

        // apply velocity
        pos->x += vel->dx * dt;
        pos->y += vel->dy * dt;
    }
}