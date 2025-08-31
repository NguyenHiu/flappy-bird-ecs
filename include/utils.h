#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Utils
{
    template <typename T>
    std::string className(T ins)
    {
        return typeid(ins).name();
    }

    template <typename T>
    std::string className()
    {
        return typeid(T).name();
    }

    inline sf::Vector2f getVectorF(sf::Vector2f vf, sf::Vector2u vu)
    {
        return {
            vf.x * vu.x,
            vf.y * vu.y};
    }

    inline sf::Vector2f getVectorF(sf::Vector2f vf, sf::Vector2i vi)
    {
        return {
            vf.x * vi.x,
            vf.y * vi.y};
    }

    inline sf::Vector2i getVectorI(sf::Vector2u vu) {
        return {
            static_cast<int>(vu.x),
            static_cast<int>(vu.y)
        };
    }

    inline bool isOverlapping(sf::IntRect r1, sf::IntRect r2)
    {
        return r2.position.x < r1.position.x + r1.size.x &&
               r1.position.x < r2.position.x + r2.size.x &&
               r2.position.y < r1.position.y + r1.size.y &&
               r1.position.y < r2.position.y + r2.size.y;
    }

} // namespace Utils
