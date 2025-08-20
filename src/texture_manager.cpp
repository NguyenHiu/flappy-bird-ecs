#include <SFML/Graphics.hpp>
#include "texture_manager.h"

void TextureManager::load(std::string path, std::string name)
{
    sf::Texture t;
    if (!t.loadFromFile(path))
    {
        Logger::Warn("Can't load texture ", path);
        return;
    }

    std::string key = (name == "" ? path : name);
    m_textures[key] = t;
}

const sf::Texture &TextureManager::get(std::string name) const
{
    auto it = m_textures.find(name);
    if (it == m_textures.end()) 
    {
        Logger::Warn("Texture not found: ", name);
        return m_defaultTexture;
    }
    
    return it->second;
}