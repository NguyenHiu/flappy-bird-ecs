#pragma once

#include <vector>
#include "abstract_system.h"
#include "entity.h"

enum class GameState {
    IDLE,
    RUN,
    END
};

class GameManager
{
private:
    GameState m_state;
    std::vector<Entity *> m_entities;
    std::vector<AbstractSystem *> m_systems;

private:
    GameManager() : m_state(GameState::IDLE) {};
    ~GameManager() {};

public:
    static GameManager &getInstance()
    {
        static GameManager instance;
        return instance;
    }
    GameState getGameState() {return this->m_state;}

    void update(float dt);
    void addEntity(Entity* entity);
    void addSystem(AbstractSystem* system);
    void initGame(sf::RenderWindow* game);
    void startGame();
    void endGame();
    void restartGame();
};