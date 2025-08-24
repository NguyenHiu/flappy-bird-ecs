#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Utils
{
    template<typename T>
    std::string className(T ins) {
        return typeid(ins).name();
    }

    template<typename T>
    std::string className() {
        return typeid(T).name();
    }

    inline sf::Vector2f getVectorF(sf::Vector2f vf, sf::Vector2u vu) {
        return {
            vf.x * vu.x,
            vf.y * vu.y
        };
    }

    inline sf::Vector2f getVectorF(sf::Vector2f vf, sf::Vector2i vi) {
        return {
            vf.x * vi.x,
            vf.y * vi.y
        };
    }

} // namespace Utils
