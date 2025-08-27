#include <unordered_map>
#include "inf_bg_system.h"
#include "component.h"

void InfBgSystem::update(std::vector<Entity *> &entities, float dt)
{
    std::unordered_map<int, Entity *> lastEntity;
    std::unordered_map<int, std::vector<Entity *>> outRangeEntities;
    std::unordered_map<int, float> sizes;
    float size;
    for (auto *entity : entities)
    {
        InfBgComponent *inf_comp = entity->getComponent<InfBgComponent>();
        PositionComponent *pos_comp = entity->getComponent<PositionComponent>();
        VelocityComponent *vel_comp = entity->getComponent<VelocityComponent>();
        if (!inf_comp || !pos_comp || !vel_comp)
        {
            continue;
        }

        // Move the entity
        vel_comp->dx -= 10;

        // Store the size of each enity
        size = inf_comp->width;
        if (sizes.find(inf_comp->tag) == sizes.end())
        {
            sizes[inf_comp->tag] = inf_comp->width;
        }

        // Check if the entity exceeds the screen bound (check left only)
        if (pos_comp->x + size < 0)
        {
            outRangeEntities[inf_comp->tag].push_back(entity);
        }
        else
        {
            auto it1 = lastEntity.find(inf_comp->tag);
            if (it1 == lastEntity.end() || it1->second->getComponent<PositionComponent>()->x < pos_comp->x)
            {
                lastEntity[inf_comp->tag] = entity;
            }
        }
    }

    // Update position of out-range sprites
    int lastX;
    for (auto it = outRangeEntities.begin(); it != outRangeEntities.end(); ++it)
    {
        if (it->second.size() <= 0)
            continue;

        lastX = 0; // Default = 0

        // Get last x value
        auto it1 = lastEntity.find(it->first);
        if (it1 != lastEntity.end())
        {
            auto itSize = sizes.find(it1->first);
            if (itSize == sizes.end())
            {
                Logger::Error("[InfBgSystem] Incorrect logic, missing size while having out-range or last data");
                return;
            }

            float size = itSize->second;
            if (it1 != lastEntity.end())
            {
                lastX = it1->second->getComponent<PositionComponent>()->x + size;
            }
        }

        for (auto* it2 : it->second) {
            it2->getComponent<PositionComponent>()->x = lastX;
            lastX += size;
        }
    }
}