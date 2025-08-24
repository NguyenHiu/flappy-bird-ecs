#include "render_system.h"
#include "component.h"
#include "logger.h"

void flipSprite(bool isFlipped, sf::Sprite &sprite)
{
    // Flip
    if (isFlipped != (sprite.getScale().x < 0))
    {
        Logger::Debug("Flipping sprite...");
        sf::Vector2f curScale = sprite.getScale();
        sprite.setScale({-curScale.x, curScale.y});
    }
}

void rotateSprite(float rotationDegrees, sf::Sprite& sprite) 
{
    if (sprite.getRotation().asDegrees() != rotationDegrees) {
        sprite.setRotation(sf::degrees(rotationDegrees));
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
            flipSprite(sc->spriteData.isFlipped, sc->spriteData.sprite);
            rotateSprite(sc->spriteData.rotationDegree, sc->spriteData.sprite);

            // Update sprite position
            if (entity->hasComponent<PositionComponent>())
            {
                PositionComponent *pc = entity->getComponent<PositionComponent>();
                sc->spriteData.sprite.setPosition({pc->x, pc->y});
            }

            m_rw->draw(sc->spriteData.sprite);
        }

        // Run animation
        if (entity->hasComponent<HSpritesheetComponent>())
        {
            HSpritesheetComponent *sc = entity->getComponent<HSpritesheetComponent>();
            flipSprite(sc->spriteData.isFlipped, sc->spriteData.sprite);
            rotateSprite(sc->spriteData.rotationDegree, sc->spriteData.sprite);

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
            sc->spriteData.sprite.setTextureRect(getIntRect(sc->curFrame, sc->frameSize));

            // Update sprite position
            if (entity->hasComponent<PositionComponent>())
            {
                PositionComponent *pc = entity->getComponent<PositionComponent>();
                sc->spriteData.sprite.setPosition({pc->x, pc->y});
            }

            m_rw->draw(sc->spriteData.sprite);
        }
    }
}