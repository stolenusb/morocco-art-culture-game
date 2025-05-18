#include <iostream>
#include "score.h"

Score::Score(sf::Font &font, sf::Vector2f fPos)
{
    loadSounds();
    iScore = 0;

    Entity.setPosition(sf::Vector2f(fPos));
    Entity.setCharacterSize(100);
    Entity.setFont(font);
    Entity.setOutlineColor(sf::Color::Black);
    Entity.setOutlineThickness(4.f);
    Entity.setFillColor(sf::Color(255, 165, 0));
    Entity.setStyle(sf::Text::Bold);
    Entity.setLetterSpacing(1.5f);
    Entity.setString("x" + std::to_string(iScore));
}

Score::~Score()
{
}

void Score::Reset()
{
    iScore = 0;
    Entity.setString("x" + std::to_string(iScore));
}

void Score::incScore()
{
    iScore++;
    sound.play();
    Entity.setString("x" + std::to_string(iScore));
}

void Score::loadSounds()
{
    if(soundBuffer.loadFromFile("..\\..\\assets\\sound\\gainscore.wav")) {
        std::cout << "(+) Loaded sound gainscore.wav"<< std::endl;
        sound.setBuffer(soundBuffer);
    } else
        std::cout << "(-) Failed to load sound gainscore.wav" << std::endl;
}