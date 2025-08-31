#include "render_system.h"
#include "component.h"
#include "logger.h"

void flipSprite(std::vector<bool> isFlipped, sf::Sprite &sprite)
{
    if (isFlipped.size() != 2)
        return;

    // Flip
    sf::Vector2f _scale = {1, 1};
    sf::Vector2f curScale = sprite.getScale();
    if (isFlipped[0] != (curScale.x < 0))
        _scale.x = -1;
    if (isFlipped[1] != (curScale.y < 0))
        _scale.y = -1;
    sprite.setScale({curScale.x * _scale.x, curScale.y * _scale.y});
}

void rotateSprite(float rotationDegrees, sf::Sprite &sprite)
{
    if (sprite.getRotation().asDegrees() != rotationDegrees)
    {
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

        // Render line pipe
        if (entity->hasComponent<LinePipeComponent>())
        {
            Logger::Debug("Trying to render line pipe component");
            LinePipeComponent *comp = entity->getComponent<LinePipeComponent>();
            SpriteComponent *top = comp->top, *bottom = comp->bottom;
            flipSprite(top->spriteData.isFlipped, top->spriteData.sprite);
            flipSprite(bottom->spriteData.isFlipped, bottom->spriteData.sprite);

            // Update sprite position
            if (entity->hasComponent<PositionComponent>())
            {
                PositionComponent *pc = entity->getComponent<PositionComponent>();
                top->spriteData.sprite.setPosition({pc->x, pc->y - comp->vSpace / 2});
                bottom->spriteData.sprite.setPosition({pc->x, pc->y + comp->vSpace / 2});
            }

            // Update sprite position
            auto *pc = entity->getComponent<PositionComponent>();
            sf::Vector2f changedPosTop = {0, 0}, changedPosBottom = {0, 0};
            if (comp != nullptr)
            {
                changedPosTop = {pc->x, pc->y - comp->vSpace / 2};
                changedPosBottom = {pc->x, pc->y + comp->vSpace / 2};
            }
            this->renderSpriteComponent(bottom->spriteData, changedPosBottom);
            this->renderSpriteComponent(top->spriteData, changedPosTop);
        }
    }
}

void RenderSystem::renderSpriteComponent(SpriteData &spriteData, sf::Vector2f newPos)
{
    flipSprite(spriteData.isFlipped, spriteData.sprite);
    rotateSprite(spriteData.rotationDegree, spriteData.sprite);
    spriteData.sprite.setPosition(newPos);
    m_rw->draw(spriteData.sprite);
}