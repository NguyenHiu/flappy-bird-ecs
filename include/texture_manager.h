#pragma once
#include <unordered_map>
#include "logger.h"

class TextureManager
{
public:
    static TextureManager &getInstance()
    {
        static TextureManager instance;
        return instance;
    }

private:
    std::unordered_map<std::string, sf::Texture> m_textures;
    sf::Texture m_defaultTexture;
    TextureManager() {};
    ~TextureManager()
    {
        Logger::Info("Cleanup TextureManager");
        m_textures.clear();
    };

public:
    void load(std::string path, std::string name = "");
    const sf::Texture& get(std::string name) const;
};