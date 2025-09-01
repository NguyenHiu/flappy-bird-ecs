#pragma once

#include "abstract_system.h"
#include "component.h"

class PipeSystem : public AbstractSystem
{
private:
    float m_startX;
    float m_centralY;
    float m_minA;
    float m_maxA;
    float m_pipeSpacingX;
    float m_minSpacingY;
    float m_maxSpacingY;
    bool m_didReseted;
    std::vector<std::pair<Entity *, Entity *>> m_pipes;
    int m_nPipes;

public:
    PipeSystem(float startX, float centralY, float minA, float maxA, float pipeSpacingX,
               float minSpacingY, float maxSpacingY)
        : m_startX(startX), m_centralY(centralY), m_minA(minA), m_maxA(maxA),
          m_nPipes(0), m_pipeSpacingX(pipeSpacingX), m_minSpacingY(minSpacingY), 
          m_maxSpacingY(maxSpacingY), m_didReseted(false)
    {
    }
    ~PipeSystem() {}

    void update(std::vector<Entity *> &entites, float dt);

private:
    void constructPipes(std::vector<Entity *> &entities);
};