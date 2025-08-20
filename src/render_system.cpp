#include "render_system.h"
#include "component.h"
#include "logger.h"

void flipSprite(bool isFlipped, sf::Sprite &sprite)
{
    // Flip
    if (isFlipped != (sprite.getScale().x == 1))
    {
        Logger::Debug("Flipping sprite...");
        sf::Vector2f curScale = sprite.getScale();
        sprite.setScale({-curScale.x, curScale.y});
    }
}

sf::IntRect getIntRect(int idx, sf::Vector2u frameSize)
{
    return sf::IntRect(
        {static_cast<int>(idx * frameSize.x),
         0},
        {static_cast<int>(frameSize.x),
         static_cast<int>(frameSize.y)});
}

void RenderSystem::update(std::vector<Entity *> &entities, float dt)
{
    for (auto *entity : entities)
    {
        // Render SpriteComponent
        if (entity->hasComponent<SpriteComponent>())
        {
            SpriteComponent *sc = entity->getComponent<SpriteComponent>();
            flipSprite(sc->isFlipped, sc->sprite);

            // Update sprite position
            if (entity->hasComponent<PositionComponent>())
            {
                PositionComponent *pc = entity->getComponent<PositionComponent>();
                sc->sprite.setPosition({pc->x, pc->y});
            }

            m_rw->draw(sc->sprite);
        }

        // Run animation
        if (entity->hasComponent<HSpritesheetComponent>())
        {
            HSpritesheetComponent *sc = entity->getComponent<HSpritesheetComponent>();
            flipSprite(sc->isFlipped, sc->sprite);

            // Update sprite frame
            sc->_curFrame += sc->fps * dt;
            sc->curFrame = static_cast<int>(sc->_curFrame);
            if (sc->curFrame >= sc->nFrame)
            {
                if (sc->isLoop) {
                    sc->_curFrame -= sc->curFrame;
                    sc->curFrame = 0;
                }
                else {
                    sc->curFrame = sc->nFrame - 1;
                }
            }
            sc->sprite.setTextureRect(getIntRect(sc->curFrame, sc->frameSize));

            // Update sprite position
            if (entity->hasComponent<PositionComponent>())
            {
                PositionComponent *pc = entity->getComponent<PositionComponent>();
                sc->sprite.setPosition({pc->x, pc->y});
            }

            m_rw->draw(sc->sprite);
        }
    }
}