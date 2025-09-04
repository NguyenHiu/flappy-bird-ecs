#include "render_system.h"
#include "component.h"
#include "logger.h"
#include "util.h"

void flipSprite(SpriteData& spriteData, sf::Sprite &sprite)
{
    if (spriteData.isFlipped.size() != 2)
        return;

    // Flip
    sf::Vector2f _scale = {1, 1};
    sf::Vector2f curScale = sprite.getScale();
    if (spriteData.isFlipped[0] != (curScale.x < 0))
        _scale.x = -1;
    if (spriteData.isFlipped[1] != (curScale.y < 0))
        _scale.y = -1;
    sprite.setScale({curScale.x * _scale.x, curScale.y * _scale.y});
}

void rotateSprite(SpriteData& spriteData, sf::Sprite &sprite)
{
    if (sprite.getRotation().asDegrees() != spriteData.rotationDegree)
    {
        sprite.setRotation(sf::degrees(spriteData.rotationDegree));
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
            auto *comp = entity->getComponent<PositionComponent>();
            sf::Vector2f changedPos = {0, 0};
            if (comp != nullptr)
                changedPos = {comp->x, comp->y};
            this->renderSpriteComponent(entity->getComponent<SpriteComponent>()->spriteData, changedPos);
        }

        // Run animation
        if (entity->hasComponent<HSpritesheetComponent>())
        {
            HSpritesheetComponent *sc = entity->getComponent<HSpritesheetComponent>();

            // Update sprite frame
            sc->_curFrame += sc->fps * dt;
            sc->curFrame = static_cast<int>(sc->_curFrame);
            if (sc->curFrame >= sc->nFrame)
            {
                if (sc->isLoop)
                {
                    sc->_curFrame -= sc->curFrame;
                    sc->curFrame = 0;
                }
                else
                {
                    sc->curFrame = sc->nFrame - 1;
                }
            }
            sc->spriteData.sprite.setTextureRect(getIntRect(sc->curFrame, sc->frameSize));

            // Update sprite position
            auto *comp = entity->getComponent<PositionComponent>();
            sf::Vector2f changedPos = {0, 0};
            if (comp != nullptr)
                changedPos = {comp->x, comp->y};
            this->renderSpriteComponent(sc->spriteData, changedPos);
        }
    }
}

void RenderSystem::renderSpriteComponent(SpriteData &spriteData, sf::Vector2f newPos)
{
    flipSprite(spriteData, spriteData.sprite);
    rotateSprite(spriteData, spriteData.sprite);
    spriteData.sprite.setPosition(newPos);
    m_rw->draw(spriteData.sprite);
}