#include "animation.h"

void Animation::loadTextures(unsigned int animations)
{
    switch(animations)
    {
        case PLAYER_ANIMS:
            if( !Texture[PLAYER_IDLE].loadFromFile("..\\..\\assets\\textures\\magician\\idle.png") ||
                !Texture[PLAYER_WALK].loadFromFile("..\\..\\assets\\textures\\magician\\walk.png") ||
                !Texture[PLAYER_RUN].loadFromFile("..\\..\\assets\\textures\\magician\\run.png") ||
                !Texture[PLAYER_JUMP].loadFromFile("..\\..\\assets\\textures\\magician\\jump.png") ||
                !Texture[PLAYER_ATTACK].loadFromFile("..\\..\\assets\\textures\\magician\\attack_1.png"))

                std::cout << "(-) Failed to load one of the player textures." << std::endl;
            else
                std::cout << "(+) Loaded player textures." << std::endl;

            break;

        case ENEMY_ANIMS:
            if( !Texture[ENEMY_IDLE].loadFromFile("..\\..\\assets\\textures\\firewizard\\Idle.png") ||
                !Texture[ENEMY_HURT].loadFromFile("..\\..\\assets\\textures\\firewizard\\Hurt.png"))
                std::cout << "(-) Failed to load one of the enemy textures." << std::endl;
            else
                std::cout << "(+) Loaded enemy textures." << std::endl;
            
            break;

        case PROJECTILE_ANIM:
            if( !Texture[PLAYER_PROJECTILE1].loadFromFile("..\\..\\assets\\textures\\magician\\charge_2.png") ||
                !Texture[PLAYER_PROJECTILE2].loadFromFile("..\\..\\assets\\textures\\magician\\charge_1.png"))
                std::cout << "(-) Failed to load player projectile texture." << std::endl;
            else
                std::cout << "(+) Loaded projectile textures." << std::endl;
            
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
    // Changing animation image every 0.14 sec
    if(clock.getElapsedTime().asSeconds() > 0.14f) {
        // If reached last animation image, initialize animation
        if(currImage >= imgCount)
            currImage = 0;
        else // Else set to next animation image
            currImage++;

        clock.restart();
    }

    //if looking right, flip image
    if(lookRight == true) {
        textureRect.width = abs(textureRect.width);
        textureRect.left = currImage * textureRect.width;
    } else { // vice versa
        textureRect.width = -abs(textureRect.width);
        textureRect.left = (currImage + 1) * abs(textureRect.width);
    }
    
    Sprite.setTexture(Texture[textureID]);
    Sprite.setTextureRect(textureRect);
}