#pragma once
#include <SFML/Graphics.hpp>

const float JUMP_COOLDOWN = 0.3f;
const float JUMP_FORCE = -500.f;
const float GRAVITY = 2000.f;
const sf::Vector2f START_POSITION = {200.f, 350.f};
const int BIRD_FPS = 10;
const std::string BIRD_TAG = "bird";
const std::string GAME_TITLE = "Nappy-Bird";
const sf::Vector2u BIRD_FRAME = {34, 24};
const float MAX_SPEED = 700.f;
const float BIRD_DEFAULT_ROTATE = -25.f;
const float ROTATE_THRESHOLD = 450.f;