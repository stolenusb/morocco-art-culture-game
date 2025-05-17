#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

enum PLAYER_ANIMATION_TEXTURES
{
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_RUN,
    PLAYER_JUMP,
    PLAYER_ATTACK,
    PLAYER_PROJECTILE1,
    PLAYER_PROJECTILE2,
    PLAYER_ANIMATION_COUNT
};

enum ENEMY_ANIMATION_TEXTURES
{
    ENEMY_IDLE,
    ENEMY_HURT,
    ENEMY_ANIMATION_COUNT
};

enum ANIMATION_TEXTURES
{
    PLAYER_ANIMS,
    ENEMY_ANIMS,
    PROJECTILE_ANIM
};


class Animation 
{
public:
    void loadTextures(unsigned int animations);
    void Animate(sf::Sprite &Sprite);
    void Set(unsigned int textureID, unsigned int imageCount, sf::Vector2u animationSize);

    bool lookRight =  true;

private:
    sf::Texture Texture[PLAYER_ANIMATION_COUNT];
    sf::IntRect textureRect;
    sf::Clock clock;
    unsigned int textureID;
    unsigned int imgCount;
    unsigned int currImage;
};