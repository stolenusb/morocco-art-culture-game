#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class Score
{
public:
    Score(sf::Font &font, sf::Vector2f fPos);
    ~Score();

    void incScore();

    int iScore;
    sf::Text Entity;
private:
    void loadSounds();
    
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
};