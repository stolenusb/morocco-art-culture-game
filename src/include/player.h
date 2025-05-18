#pragma once

#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "animation.h"
#include "collision.h"

class Player
{
public:
    Player(sf::RenderWindow &window, sf::Vector2f entitySize, float Scale, float moveSpeed, float jumpForce);
    ~Player();

    void Update();
    void Draw();
    void resetPosition();

    Collider collider;
    bool Dead = false;
private:
    void setPosition(float x, float y);
    void Input();

    sf::Clock clock;
    sf::RenderWindow &window;

    sf::Vector2f entitySize;
    sf::RectangleShape Entity;
    sf::Sprite Sprite;

    Animation animation;

    sf::Vector2f Velocity;
    float moveSpeed;
    float jumpForce;
};