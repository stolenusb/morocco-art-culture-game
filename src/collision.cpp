#include <collision.h>

Collider::Collider(sf::RectangleShape &Entity, sf::Sprite &Sprite, sf::Vector2f &Velocity) :
    playerEntity(Entity), playerSprite(Sprite), playerVelocity(Velocity)
{
}

Collider::~Collider()
{
}

void Collider::playerMove(double x, double y)
{
    playerEntity.move(x, y);
    playerSprite.move(x, y);
}

bool Collider::checkCollision(sf::RectangleShape &otherEntity)
{
    // Get entities Position & half size
    sf::Vector2f otherEntityHalfSize = otherEntity.getSize() / 2.0f;
    sf::Vector2f otherEntityPosition = otherEntity.getPosition() + otherEntityHalfSize;
    
    sf::Vector2f playerEntityHalfSize = playerEntity.getSize() / 2.0f;
    sf::Vector2f playerEntityPosition = playerEntity.getPosition() + playerEntityHalfSize;
    
    // Entities Position difference
    float deltaX = otherEntityPosition.x - playerEntityPosition.x;
    float deltaY = otherEntityPosition.y - playerEntityPosition.y;
    
    // Entities get intersection
    float intersectX = abs(deltaX) - (otherEntityHalfSize.x + playerEntityHalfSize.x);
    float intersectY = abs(deltaY) - (otherEntityHalfSize.y + playerEntityHalfSize.y);
    
    // If outside entity intersecting with player
    if(intersectX <= 0.0f && intersectY <= 0.0f) {
        // Intersecting on the x axis
        if(intersectX > intersectY) {
            if(deltaX > 0.0f) // intersection from right
                playerMove(intersectX, 0.0f);
            else // intersection from left
                playerMove(-intersectX, 0.0f);
            
            playerVelocity.x = 0.0f;
        }
        // Intersecting on the Y axis
        else {
            if(deltaY > 0.0f) { // intersection from bottom
                playerMove(0.0f, intersectY);
                bCollidingWithGround = true;
            } else { // intersection from top
                playerMove(0.0f, -intersectY);
            }
            
            playerVelocity.y = 0.0f;
        }

        return true;
    }

    return false;
}