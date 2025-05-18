#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#define HEARTS_COUNT 3
class Hearts
{
public:
    Hearts(sf::Vector2f fSize, sf::Vector2f fPos);
    ~Hearts();

    void decHearts();
    void Reset();

    int iHearts;
    
    sf::RectangleShape Entity;
private:
    void loadTextures();
    void loadSounds();
    
    sf::Texture heartTextures[HEARTS_COUNT + 1];
    sf::SoundBuffer heartSound;
    sf::Sound sound;
};