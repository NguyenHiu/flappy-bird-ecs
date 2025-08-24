#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include "key_map.h"
#include "entity.h"

struct PositionComponent
{
    float x, y;
    PositionComponent(float x = 0, float y = 0) : x(x), y(y) {}
};

struct VelocityComponent
{
    float dx, dy;
    float maxSpeed;
    VelocityComponent(float dx = 0, float dy = 0, float maxSpeed = 200.f)
        : dx(dx), dy(dy), maxSpeed(maxSpeed) {}
};

struct PhysicComponent
{
    bool hasGravity;
    bool onGround;
    float gravityScale;
    float jumpCooldown;
    float jumpTimer;
    float jumpForce;
    PhysicComponent(bool gravity = true, float jumpCooldown = 1.5f, float jumpForce = 600.f, float scale = 1.0f)
        : hasGravity(gravity), onGround(false), gravityScale(scale), jumpCooldown(jumpCooldown), jumpForce(jumpForce)
    {
    }
};

// TODO: add z order
struct SpriteComponent
{
    sf::Sprite sprite;
    std::string name;
    bool isFlipped;
    float rotationDegree;
    SpriteComponent(const sf::Texture &texture, std::string name = "", bool isFlipped = false)
        : sprite(texture), name(name), isFlipped(isFlipped), rotationDegree(0)
    {
        sprite.setOrigin(sprite.getGlobalBounds().size / 2.0f);
    }
};

// Horizontal Spritesheet component
struct HSpritesheetComponent
{
    sf::Sprite sprite;
    int fps;
    std::string name;
    bool isFlipped;
    sf::Vector2u frameSize;
    int curFrame;
    float _curFrame;
    int nFrame;
    bool isLoop;
    float rotationDegree;
    HSpritesheetComponent(const sf::Texture &texture, int fps, std::string name = "",
                          bool isFlipped = false, sf::Vector2u frameSize = {0, 0})
        : sprite(texture), fps(fps), name(name),
          isFlipped(isFlipped), frameSize(frameSize),
          curFrame(0), _curFrame(0), nFrame(1),
          isLoop(true), rotationDegree(0)
    {
        if (frameSize.x != 0)
        {
            nFrame = texture.getSize().x / frameSize.x;
        }

        sprite.setOrigin({static_cast<float>(frameSize.x) / 2.f, static_cast<float>(frameSize.y) / 2.f});
    }
};

struct InputComponent
{
    std::vector<GameAction> listendedActions;
    EntityType entityType;
    InputComponent(std::vector<GameAction> actions, EntityType type)
        : listendedActions(actions), entityType(type)
    {
    }
};