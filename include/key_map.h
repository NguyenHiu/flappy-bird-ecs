#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

enum class GameAction
{
    NONE,
    JUMP,
    RESTART
};

class KeyMap
{
private:
    std::unordered_map<sf::Keyboard::Key, GameAction> m_keyToAction;
    std::unordered_map<GameAction, sf::Keyboard::Key> m_actionToKey;

public:
    KeyMap()
    {
        setKeyBinding(sf::Keyboard::Key::Space, GameAction::JUMP);
        setKeyBinding(sf::Keyboard::Key::Escape, GameAction::RESTART);
    }

    void setKeyBinding(sf::Keyboard::Key key, GameAction action)
    {
        m_keyToAction[key] = action;
        m_actionToKey[action] = key;
    }

    GameAction getAction(sf::Keyboard::Key key) const
    {
        auto it = m_keyToAction.find(key);
        return it != m_keyToAction.end() ? it->second : GameAction::NONE;
    }

    sf::Keyboard::Key getKey(GameAction action) const
    {
        auto it = m_actionToKey.find(action);
        return it != m_actionToKey.end() ? it->second : sf::Keyboard::Key::Unknown;
    }

    bool isActionPressed(GameAction action) const
    {
        auto key = getKey(action);
        return key != sf::Keyboard::Key::Unknown && sf::Keyboard::isKeyPressed(key);
    }
};