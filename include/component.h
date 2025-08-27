#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include "key_map.h"
#include "entity.h"
#include "logger.h"
#include "utils.h"

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

struct SpriteData
{
    sf::Sprite sprite;
    std::string name;
    bool isFlipped;
    float rotationDegree;
    float scaleVal;
    SpriteData(const sf::Texture &texture, std::string name = "", bool isFlipped = false, float scaleVal = 1.f, sf::Vector2f origin = {0, 0})
        : sprite(texture), name(name), isFlipped(isFlipped), rotationDegree(0), scaleVal(scaleVal)
    {
        sprite.setOrigin(origin);
        sprite.setScale({scaleVal, scaleVal});
    }
};

// TODO: add z order
struct SpriteComponent
{
    SpriteData spriteData;

    SpriteComponent(
        const sf::Texture &texture, std::string name = "",
        bool isFlipped = false, float scaleVal = 1.f, sf::Vector2f originRatio = {0.5, 0.5}
    ) : spriteData(texture, name, isFlipped, scaleVal, Utils::getVectorF(originRatio, texture.getSize()))
    {
    }
};

// Horizontal Spritesheet component
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
                          bool isFlipped = false, sf::Vector2u frameSize = {0, 0},
                          float scaleVal = 1.f, sf::Vector2f originRatio = {0.5, 0.5})
        : spriteData(texture, name, isFlipped, scaleVal, Utils::getVectorF(originRatio, frameSize)), fps(fps),
          frameSize(frameSize), curFrame(0), _curFrame(0), nFrame(1), isLoop(true)
    {
        if (frameSize.x != 0)
            nFrame = texture.getSize().x / frameSize.x;
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

struct BirdRotateComponent {
    float defaultAngle;
    float threshold;
    BirdRotateComponent(float defaultAngle = -25.f, float threshold = 50.f)
        : defaultAngle(defaultAngle), threshold(threshold)
        {}
};

struct InfBgComponent {
    int tag;
    float width;
    InfBgComponent(int tag, float width) : tag(tag), width(width) {}
};