#include "animation.h"

void Animation::loadTextures(unsigned int animations)
{
    switch(animations) {
        case PLAYER_ANIMS:
            if( !Texture[PLAYER_IDLE].loadFromFile("..\\..\\assets\\textures\\magician\\idle.png") ||
                !Texture[PLAYER_WALK].loadFromFile("..\\..\\assets\\textures\\magician\\walk.png") ||
                !Texture[PLAYER_RUN].loadFromFile("..\\..\\assets\\textures\\magician\\run.png") ||
                !Texture[PLAYER_JUMP].loadFromFile("..\\..\\assets\\textures\\magician\\jump.png") ||
                !Texture[PLAYER_DEAD].loadFromFile("..\\..\\assets\\textures\\magician\\Dead.png"))

                std::cout << "(-) Failed to load one of the player textures." << std::endl;
            else
                std::cout << "(+) Loaded player textures." << std::endl;

            break;
        
        case DOG_ANIMS:
            if( !Texture[DOG_BARK].loadFromFile("..\\..\\assets\\textures\\dog.png"))
                std::cout << "(-) Failed to load dog texture." << std::endl;
            else
                std::cout << "(+) Loaded dog texture." << std::endl;
            
            break;
    }
}

void Animation::Set(unsigned int textureID, unsigned int imageCount, sf::Vector2u animationSize)
{
    imgCount = imageCount - 1;
    this->textureID = textureID;
    textureRect = sf::IntRect(0, 0, animationSize.x, animationSize.y);
}

void Animation::Animate(sf::Sprite &Sprite)
{
    if(stopAnim)
        return;
    
    if(clock.getElapsedTime().asSeconds() > 0.14f) {
        if(currImage >= imgCount)
            currImage = 0;
        else
            currImage++;

        clock.restart();
    }

    if(lookRight == true) {
        textureRect.width = abs(textureRect.width);
        textureRect.left = currImage * textureRect.width;
    } else {
        textureRect.width = -abs(textureRect.width);
        textureRect.left = (currImage + 1) * abs(textureRect.width);
    }
    
    Sprite.setTexture(Texture[textureID]);
    Sprite.setTextureRect(textureRect);

    if(textureID == PLAYER_DEAD && currImage == imgCount)
        stopAnim = true;
}