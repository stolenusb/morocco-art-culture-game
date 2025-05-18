#include <iostream>
#include "hearts.h"

Hearts::Hearts(sf::Vector2f fSize, sf::Vector2f fPos)
{
    loadTextures();
    loadSounds();
    Entity.setSize(fSize);
    Entity.setPosition(fPos);
    Reset();
}

Hearts::~Hearts()
{
}

void Hearts::loadTextures()
{
    for(int i = 0; i <= HEARTS_COUNT; i++) {
        if(heartTextures[i].loadFromFile("..\\..\\assets\\textures\\hearts\\hearts_" + std::to_string(i) + ".png")) {
            std::cout << "(+) Loaded hearts_" << i << " texture." << std::endl;
        } else {
            std::cout << "(-) Failed to load hearts_" << i << " texture" << std::endl;
        }
    }
}

void Hearts::loadSounds()
{
    if(heartSound.loadFromFile("..\\..\\assets\\sound\\loseheart.wav")) {
        std::cout << "(+) Loaded sound loseheart.wav"<< std::endl;
        sound.setBuffer(heartSound);
    } else
        std::cout << "(-) Failed to load sound loseheart.wav" << std::endl;
}

void Hearts::Reset()
{
    Entity.setTexture(&heartTextures[HEARTS_COUNT]);
    iHearts = HEARTS_COUNT;
}

void Hearts::decHearts()
{
    iHearts--;
    sound.play();
    Entity.setTexture(&heartTextures[iHearts]);
}