#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include "texture_manager.h"
#include "key_map.h"
#include "entity.h"
#include "logger.h"
#include "utils.h"

/// Position Component
struct PositionComponent
{
    float x, y;
    PositionComponent(float x = 0, float y = 0) : x(x), y(y) {}
};

/// Velocity Component
struct VelocityComponent
{
    float dx, dy;
    float maxSpeed;
    VelocityComponent(float dx = 0, float dy = 0, float maxSpeed = 200.f)
        : dx(dx), dy(dy), maxSpeed(maxSpeed) {}
};

/// Physic Component
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

/// Sprite Data (Used in Sprite Component & HSpritesheet Component)
struct SpriteData
{
    sf::Sprite sprite;
    std::string name;
    std::vector<bool> isFlipped;
    float rotationDegree;
    float scaleVal;
    SpriteData(const sf::Texture &texture, std::string name = "", float scaleVal = 1.f, sf::Vector2f origin = {0, 0})
        : sprite(texture), name(name), isFlipped({false, false}), rotationDegree(0), scaleVal(scaleVal)
    {
        sprite.setOrigin(origin);
        sprite.setScale({scaleVal, scaleVal});
    }
};

// TODO: add z order
/// Sprite Component
struct SpriteComponent
{
    SpriteData spriteData;

    SpriteComponent(
        const sf::Texture &texture, std::string name = "",
        float scaleVal = 1.f, sf::Vector2f originRatio = {0.5, 0.5}) : spriteData(texture, name, scaleVal, Utils::getVectorF(originRatio, texture.getSize()))
    {
    }
};

/// Horizontal Spritesheet Component
struct HSpritesheetComponent
{
    SpriteData spriteData;
    int fps;
    sf::Vector2u frameSize;
    int curFrame;
    float _curFrame;
    int nFrame;
    bool isLoop;
    HSpritesheetComponent(const sf::Texture &texture, int fps, std::string name = "",
                          sf::Vector2u frameSize = {0, 0}, float scaleVal = 1.f, sf::Vector2f originRatio = {0.5, 0.5})
        : spriteData(texture, name, scaleVal, Utils::getVectorF(originRatio, frameSize)), fps(fps),
          frameSize(frameSize), curFrame(0), _curFrame(0), nFrame(1), isLoop(true)
    {
        if (frameSize.x != 0)
            nFrame = texture.getSize().x / frameSize.x;
    }
};

/// Input Component
struct InputComponent
{
    std::vector<GameAction> listendedActions;
    InputComponent(std::vector<GameAction> actions)
        : listendedActions(actions)
    {
    }
};

/// Bird Rotate Component
struct BirdRotateComponent
{
    float defaultAngle;
    float threshold;
    BirdRotateComponent(float defaultAngle = -25.f, float threshold = 50.f)
        : defaultAngle(defaultAngle), threshold(threshold)
    {
    }
};

/// Infinity Background Component
struct InfBgComponent
{
    int tag;
    float width;
    InfBgComponent(int tag, float width) : tag(tag), width(width) {}
};