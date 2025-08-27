#include <SFML/Graphics.hpp>
#include "texture_manager.h"
#include "game_manager.h"
#include "render_system.h"
#include "physics_system.h"
#include "input_system.h"
#include "inf_bg_system.h"
#include "component.h"

const float JUMP_COOLDOWN = 0.3f;
const float JUMP_FORCE = -500.f;
const float GRAVITY = 1800.f;
const sf::Vector2f START_POSITION = {200.f, 350.f};
const int BIRD_FPS = 10;
const std::string BIRD_TAG = "bird";
const std::string GAME_TITLE = "Nappy-Bird";
const sf::Vector2u BIRD_FRAME = {34, 24};
const float MAX_SPEED = 500.f;
const float BIRD_DEFAULT_ROTATE = -25.f;
const float ROTATE_THRESHOLD = 200.f;

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
    RenderSystem* system_rd = new RenderSystem(game);
    gMgr.addSystem(system_rd);
    PhysicsSystem* system_ps = new PhysicsSystem(GRAVITY);
    gMgr.addSystem(system_ps);
    InputSystem* system_input = new InputSystem(nullptr);
    gMgr.addSystem(system_input);
    InfBgSystem* system_infBg = new InfBgSystem();
    gMgr.addSystem(system_infBg);

    Entity* background = new Entity();
    SpriteComponent* bg_comp_sprite = new SpriteComponent(tMgr.get("background"), "background", false, 1.5, {0, 0});
    background->addComponent(bg_comp_sprite);
    PositionComponent* bg_comp_pos = new PositionComponent(0, 0);
    background->addComponent(bg_comp_pos);
    gMgr.addEntity(background);

    Entity* ground = new Entity();
    SpriteComponent* gr_comp_sprite = new SpriteComponent(tMgr.get("base"), "base", false, 1, {0, 0});
    ground->addComponent(gr_comp_sprite);
    PositionComponent* gr_comp_pos = new PositionComponent(0, START_POSITION.y*2-tMgr.get("base").getSize().y);
    ground->addComponent(gr_comp_pos);
    PhysicComponent* gr_comp_phy = new PhysicComponent(false, 0, 0, 0);
    ground->addComponent(gr_comp_phy);
    InfBgComponent* gr_comp_infBg = new InfBgComponent(1, tMgr.get("base").getSize().x);
    ground->addComponent(gr_comp_infBg);
    VelocityComponent* gr_comp_vel = new VelocityComponent(0, 0, 150.f);
    ground->addComponent(gr_comp_vel);
    gMgr.addEntity(ground);

    Entity* ground1 = new Entity();
    SpriteComponent* gr1_comp_sprite = new SpriteComponent(tMgr.get("base"), "base", false, 1, {0, 0});
    ground1->addComponent(gr1_comp_sprite);
    PositionComponent* gr1_comp_pos = new PositionComponent(tMgr.get("base").getSize().x, START_POSITION.y*2-tMgr.get("base").getSize().y);
    ground1->addComponent(gr1_comp_pos);
    PhysicComponent* gr1_comp_phy = new PhysicComponent(false, 0, 0, 0);
    ground1->addComponent(gr1_comp_phy);
    InfBgComponent* gr1_comp_infBg = new InfBgComponent(1, tMgr.get("base").getSize().x);
    ground1->addComponent(gr1_comp_infBg);
    VelocityComponent* gr1_comp_vel = new VelocityComponent(0, 0, 150.f);
    ground1->addComponent(gr1_comp_vel);
    gMgr.addEntity(ground1);

    Entity* ground2 = new Entity();
    SpriteComponent* gr2_comp_sprite = new SpriteComponent(tMgr.get("base"), "base", false, 1, {0, 0});
    ground2->addComponent(gr2_comp_sprite);
    PositionComponent* gr2_comp_pos = new PositionComponent(tMgr.get("base").getSize().x*2, START_POSITION.y*2-tMgr.get("base").getSize().y);
    ground2->addComponent(gr2_comp_pos);
    PhysicComponent* gr2_comp_phy = new PhysicComponent(false, 0, 0, 0);
    ground2->addComponent(gr2_comp_phy);
    InfBgComponent* gr2_comp_infBg = new InfBgComponent(1, tMgr.get("base").getSize().x);
    ground2->addComponent(gr2_comp_infBg);
    VelocityComponent* gr2_comp_vel = new VelocityComponent(0, 0, 150.f);
    ground2->addComponent(gr2_comp_vel);
    gMgr.addEntity(ground2);

    Entity* bird = new Entity();
    PhysicComponent* comp_physic = new PhysicComponent(true, JUMP_COOLDOWN, JUMP_FORCE, 1);
    bird->addComponent(comp_physic);
    PositionComponent* comp_pos = new PositionComponent(START_POSITION.x, START_POSITION.y);
    bird->addComponent(comp_pos);
    VelocityComponent* comp_vel = new VelocityComponent(0, 0, MAX_SPEED);
    bird->addComponent(comp_vel);
    // SpriteComponent* spriteComp = new SpriteComponent(tMgr.get("bird"), "bird");
    // bird->addComponent(spriteComp);
    HSpritesheetComponent* comp_anim = new HSpritesheetComponent(tMgr.get(BIRD_TAG), BIRD_FPS, BIRD_TAG, false, BIRD_FRAME, 1.2);
    bird->addComponent(comp_anim);
    InputComponent* comp_input = new InputComponent({GameAction::JUMP}, EntityType::PLAYER);
    bird->addComponent(comp_input);
    BirdRotateComponent* comp_birdRotate = new BirdRotateComponent(BIRD_DEFAULT_ROTATE, ROTATE_THRESHOLD);
    bird->addComponent(comp_birdRotate);

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