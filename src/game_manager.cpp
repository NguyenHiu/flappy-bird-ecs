#include "game_manager.h"
#include "texture_manager.h"
#include "game_config.h"
#include "logger.h"
#include "render_system.h"
#include "physics_system.h"
#include "input_system.h"
#include "inf_bg_system.h"
#include "box_collider_system.h"
#include "pipe_system.h"
#include "component.h"

void GameManager::update(float dt)
{
    for (auto *system : m_systems)
    {
        system->update(m_entities, dt);
    }
    // Logger::Debug("Complete game update");
}

void GameManager::addEntity(Entity *entity)
{
    m_entities.push_back(entity);
}

void GameManager::addSystem(AbstractSystem *system)
{
    m_systems.push_back(system);
}

void GameManager::initGame(sf::RenderWindow *game)
{
    TextureManager &tMgr = TextureManager::getInstance();

    // Init systems
    this->addSystem(new RenderSystem(game));
    this->addSystem(new PhysicsSystem(GRAVITY));
    this->addSystem(new InputSystem(nullptr));
    this->addSystem(new InfBgSystem());
    this->addSystem(new BoxColliderSystem());
    this->addSystem(new PipeSystem(START_POSITION.x * 3 + 10, START_POSITION.y, -50, 50, 250, 75, 125));

    // Init background
    Entity *background = new Entity(EntityType::BACKGROUND);
    background->addComponent(new SpriteComponent(tMgr.get("background"), "background", 1.5, {0, 0}));
    background->addComponent(new PositionComponent(0, 0));
    this->addEntity(background);

    // Init pipes
    const int nPipes = 10;
    const float pipeScaleVal = 1.5f;
    const sf::Texture &pipeTxt = tMgr.get("pipe");
    for (int i = 0; i < nPipes; ++i)
    {
        Entity *pipe = new Entity(EntityType::PIPE);
        pipe->addComponent(new SpriteComponent(pipeTxt, "pipe", pipeScaleVal, {0, 0}));
        pipe->addComponent(new PositionComponent());
        pipe->addComponent(new PhysicComponent(false));
        pipe->addComponent(new VelocityComponent(-150.f));
        this->addEntity(pipe);
    }

    // Init ground
    sf::Vector2u baseSize = tMgr.get("base").getSize();
    for (int i = 0; i < 3; ++i)
    {
        Entity *ground = new Entity(EntityType::GROUND);
        ground->addComponent(new SpriteComponent(tMgr.get("base"), "base", 1, {0, 0}));
        ground->addComponent(new PositionComponent(i * baseSize.x, START_POSITION.y * 2 - baseSize.y));
        ground->addComponent(new PhysicComponent(false, 0, 0, 0));
        ground->addComponent(new InfBgComponent(1, baseSize.x));
        ground->addComponent(new VelocityComponent(-150.f, 0, 150.f));
        this->addEntity(ground);
    }

    // Init bird
    Entity *bird = new Entity(EntityType::BIRD);
    bird->addComponent(new PhysicComponent(true, JUMP_COOLDOWN, JUMP_FORCE, 1));
    bird->addComponent(new PositionComponent(START_POSITION.x, START_POSITION.y));
    bird->addComponent(new VelocityComponent(0, 0, MAX_SPEED));
    // bird->addComponent(new SpriteComponent(tMgr.get("bird"), "bird"));
    const float birdScaleVal = 1.5f;
    bird->addComponent(new HSpritesheetComponent(tMgr.get(BIRD_TAG), BIRD_FPS, BIRD_TAG, BIRD_FRAME, birdScaleVal));
    bird->addComponent(new InputComponent({GameAction::JUMP}));
    bird->addComponent(new BirdRotateComponent(BIRD_DEFAULT_ROTATE, ROTATE_THRESHOLD));
    this->addEntity(bird);

    this->m_state = GameState::IDLE;
}

void GameManager::startGame()
{
    this->m_state = GameState::RUN;
}

void GameManager::endGame()
{
    // Assume: restart game immediately
    this->restartGame();
}

void GameManager::restartGame()
{
    this->m_state = GameState::IDLE;

    for (auto *entity : m_entities)
    {
        switch (entity->getType())
        {
        case EntityType::BIRD:
        {
            PositionComponent *posComp = entity->getComponent<PositionComponent>();
            posComp->x = START_POSITION.x;
            posComp->y = START_POSITION.y;
            entity->getComponent<HSpritesheetComponent>()->spriteData.rotationDegree = 0.f;
            break;
        }

        default:
            break;
        }
    }
}