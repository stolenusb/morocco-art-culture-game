#pragma once

#include <SFML/Graphics.hpp>

class Platform
{
public:
    Platform(std::string texture, sf::Vector2f fSize, sf::Vector2f fPos);
    ~Platform();

    sf::RectangleShape Entity;

private:
    sf::Texture platformTexture;
    sf::Vector2f platformSize;
    sf::Vector2f platformPosition;
};