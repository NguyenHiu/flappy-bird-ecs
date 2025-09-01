#include "pipe_system.h"
#include "component.h"
#include "game_manager.h"

void PipeSystem::update(std::vector<Entity *> &entites, float dt)
{
    if (m_pipes.size() == 0 || GameManager::getInstance().getGameState() == GameState::IDLE) {
        this->constructPipes(entites);
    } else {
        // Simulate a pipe pool
        int nPipes = m_pipes.size();
        while (true) 
        {
            SpriteComponent* sc = m_pipes[0].first->getComponent<SpriteComponent>();
            PositionComponent* pc = m_pipes[0].first->getComponent<PositionComponent>();
            if (pc->x + sc->spriteData.sprite.getGlobalBounds().size.x < -10)
            {
                int randY = Utils::randInt(m_minA, m_maxA);
                int randA = Utils::randInt(m_minSpacingY, m_maxSpacingY);
                pc->x = m_pipes[nPipes-1].first->getComponent<PositionComponent>()->x + m_pipeSpacingX;
                pc->y = m_centralY + randY - randA;
                PositionComponent* bpc = m_pipes[0].second->getComponent<PositionComponent>();
                bpc->x = pc->x;
                bpc->y = m_centralY + randY + randA;
                std::rotate(m_pipes.begin(), m_pipes.begin()+1, m_pipes.end());
            } else {
                break;
            }
        }
    }
}

void PipeSystem::constructPipes(std::vector<Entity *> &entities)
{
    m_pipes = {};

    float startX = m_startX;

    // Construct pipes as pairs
    Entity *top = nullptr;
    for (auto *entity : entities)
    {
        if (entity->getType() == EntityType::PIPE)
        {
            bool sc = entity->hasComponent<SpriteComponent>();
            bool pc = entity->hasComponent<PositionComponent>();
            if (!sc || !pc)
            {
                Logger::Warn("Pipe should have SpriteComponent, PositionComponent");
                return;
            }
            if (top != nullptr)
            {
                entity->getComponent<SpriteComponent>()->spriteData.isFlipped = {false, false};
                PositionComponent* bottomPC = entity->getComponent<PositionComponent>();
                PositionComponent* topPC = top->getComponent<PositionComponent>();
                int randY = Utils::randInt(m_minA, m_maxA);
                int randA = Utils::randInt(m_minSpacingY, m_maxSpacingY);
                bottomPC->x = startX;
                bottomPC->y = m_centralY + randY + randA;
                topPC->x = startX;
                topPC->y = m_centralY + randY - randA;
                startX += m_pipeSpacingX;
                m_pipes.push_back({top, entity});
                top = nullptr;
            }
            else
            {
                top = entity;
                top->getComponent<SpriteComponent>()->spriteData.isFlipped = {false, true};
            }
        }
    }
}