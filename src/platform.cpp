#include <iostream>
#include "platform.h"

Platform::Platform(std::string textureFile, sf::Vector2f fSize, sf::Vector2f fPos) :
    platformSize(fSize), platformPosition(fPos)
{
    Entity.setSize(platformSize);
    Entity.setPosition(platformPosition);

    if(textureFile.empty())
        Entity.setFillColor(sf::Color::Blue);
    
    else {
        if(platformTexture.loadFromFile("..\\..\\assets\\textures\\" + textureFile)) {
            Entity.setTexture(&platformTexture);
            std::cout << "(+) Loaded " << textureFile << " texture." << std::endl;
        } else if(!platformTexture.loadFromFile("..\\..\\assets\\textures\\" + textureFile)) {
            Entity.setFillColor(sf::Color::Red);
            std::cout << "(-) Failed to load " << textureFile << " texture" << std::endl;
        }
    }
}

Platform::~Platform()
{
}