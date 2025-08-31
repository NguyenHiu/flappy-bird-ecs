#include <SFML/Graphics.hpp>
#include "texture_manager.h"
#include "game_manager.h"
#include "game_config.h"

void loadResources() {
    TextureManager& tMgr = TextureManager::getInstance();
    tMgr.load("./assets/sprites/bird-spritesheet.png", "bird");
    tMgr.load("./assets/sprites/pipe-green.png", "pipe");
    tMgr.load("./assets/sprites/base.png", "base");
    tMgr.load("./assets/sprites/background-day.png", "background");
}

int main() {
    loadResources();
    TextureManager& tMgr = TextureManager::getInstance(); // Later, we will create factory to create these components?

    sf::Vector2u gameSize = {400, 700};
    sf::RenderWindow* game = new sf::RenderWindow(sf::VideoMode(gameSize), GAME_TITLE);

    GameManager& gMgr = GameManager::getInstance();
    gMgr.initGame(game);

    sf::Clock clock;
    while(game->isOpen()) {
        while(const auto event = game->pollEvent()) {
            if (event->is<sf::Event::Closed>()) 
                game->close();
        }

        float dt = clock.restart().asSeconds();
        game->clear();
        gMgr.update(dt);
        game->display();
    }
}