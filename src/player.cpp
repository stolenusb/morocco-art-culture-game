#include "player.h"

Player::Player(sf::RenderWindow &window, sf::Vector2f entitySize, float Scale, float moveSpeed, float jumpForce) :
    window(window),
    entitySize(entitySize),
    moveSpeed(moveSpeed),
    jumpForce(jumpForce),
    collider(Entity, Sprite, Velocity)
{
    animation.loadTextures(PLAYER_ANIMS);

    // Initial player position
    resetPosition();

    Entity.setSize(entitySize);
    Sprite.setScale(sf::Vector2f(Scale, Scale));
    Entity.setFillColor(sf::Color::Transparent);
    //For debug only:
    //Entity.setOutlineThickness(1.0f);
}

Player::~Player()
{
}

void Player::Update()
{
    double deltaTime = clock.restart().asSeconds();

    // Frame Initialization
    if(collider.bCollidingWithGround)
        Velocity.x = 0.f;
    
    Velocity.y += 9.8f;
    
    if(!Dead)
        animation.Set(PLAYER_IDLE, 8, sf::Vector2u(128, 128));
    else
        animation.Set(PLAYER_DEAD, 4, sf::Vector2u(128, 128));

    // Input
    Input();

    // Update
    animation.Animate(Sprite);

    Entity.move(Velocity.x * deltaTime, Velocity.y * deltaTime);
    Sprite.move(Velocity.x * deltaTime, Velocity.y * deltaTime);
}

void Player::Input()
{
    if(Dead)
        return;
    
    if(collider.bCollidingWithGround)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            animation.lookRight = true;
            
            Velocity.x = moveSpeed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            animation.lookRight = false;

            Velocity.x = -moveSpeed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))) {
            animation.Set(PLAYER_RUN, 8, sf::Vector2u(128, 128));
            Velocity.x *= 1.9f;
        }

        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)))
            animation.Set(PLAYER_WALK, 7, sf::Vector2u(128, 128));
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            animation.Set(PLAYER_JUMP, 6, sf::Vector2u(128, 128));
            Velocity.y -= jumpForce;
            collider.bCollidingWithGround = false;
        }
    }

    else
        animation.Set(PLAYER_JUMP, 6, sf::Vector2u(128, 128));
}

void Player::Draw()
{
    window.draw(Sprite);
    window.draw(Entity);
}

void Player::setPosition(float x, float y)
{
    Entity.setPosition(x, y);
    Sprite.setPosition(x - entitySize.x, y - entitySize.y);
}

void Player::resetPosition()
{
    Velocity.x = 0.f;
    Velocity.y = 0.f;
    setPosition(float(window.getSize().x / 2) - entitySize.x, float(window.getSize().y / 2));
    animation.stopAnim = false;
    Dead = false;
}