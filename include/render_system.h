#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "abstract_system.h"
#include "component.h"

class RenderSystem : public AbstractSystem
{
private:
    sf::RenderWindow *m_rw;

public:
    RenderSystem(sf::RenderWindow *rw) : m_rw(rw) {};
    ~RenderSystem() {};
    void update(std::vector<Entity *> &entities, float dt);

private:
    void renderSpriteComponent(SpriteData& sc, sf::Vector2f newPos);
};