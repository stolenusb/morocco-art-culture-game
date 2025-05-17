#pragma once

#include <SFML/Graphics.hpp>

class Collider
{
public:
    Collider(sf::RectangleShape &Entity, sf::Sprite &Sprite, sf::Vector2f &Velocity);
    ~Collider();
    
    void playerMove(double x, double y);
    bool checkCollision(sf::RectangleShape &otherEntity);

    bool bCollidingWithGround;

private:
    sf::RectangleShape &playerEntity;
    sf::Sprite &playerSprite;
    sf::Vector2f &playerVelocity;
};