#include <SFML/Graphics.hpp>
#include "texture_manager.h"
#include "game_manager.h"
#include "render_system.h"
#include "component.h"

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
    sf::RenderWindow* game = new sf::RenderWindow(sf::VideoMode(gameSize), "Flappy-Bird");

    GameManager& gMgr = GameManager::getInstance();
    RenderSystem* system_rd = new RenderSystem(game);
    gMgr.addSystem(system_rd);

    Entity* bird = new Entity();
    PhysicComponent* physicComp = new PhysicComponent(false);
    bird->addComponent(physicComp);
    PositionComponent* positionComp = new PositionComponent(200.0, 350.0);
    bird->addComponent(positionComp);
    // SpriteComponent* spriteComp = new SpriteComponent(tMgr.get("bird"), "bird");
    // bird->addComponent(spriteComp);
    HSpritesheetComponent* animationComp = new HSpritesheetComponent(tMgr.get("bird"), 10, "bird", true, {34, 24});
    bird->addComponent(animationComp);

    gMgr.addEntity(bird);

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