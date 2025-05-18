#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

enum PLAYER_ANIMATION_TEXTURES
{
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_RUN,
    PLAYER_JUMP,
    PLAYER_DEAD,
    PLAYER_ANIMATION_COUNT
};

enum DOG_ANIMATION_TEXTURES
{
    DOG_BARK,
    DOG_ANIMS_COUNT
};

enum ANIMATION_TEXTURES
{
    PLAYER_ANIMS,
    DOG_ANIMS
};


class Animation 
{
public:
    void loadTextures(unsigned int animations);
    void Animate(sf::Sprite &Sprite);
    void Set(unsigned int textureID, unsigned int imageCount, sf::Vector2u animationSize);

    bool lookRight =  true;
    bool stopAnim = false;
private:
    sf::Texture Texture[PLAYER_ANIMATION_COUNT];
    sf::IntRect textureRect;
    sf::Clock clock;
    unsigned int textureID;
    unsigned int imgCount;
    unsigned int currImage;
};