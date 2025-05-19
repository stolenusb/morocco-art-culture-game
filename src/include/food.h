#pragma once

#include <SFML/Graphics.hpp>
#include "player.h"
#include "hearts.h"
#include "score.h"

#define FOOD_SIZE_X 96
#define FOOD_SIZE_Y 96
enum FOOD_ENUM {
    FOOD_BAGHRIR,
    FOOD_CHEBAKIA,
    FOOD_COUSCOUS,
    FOOD_KEBAB,
    FOOD_NOODLES,
    FOOD_PIZZA,
    FOOD_SPAGHETTI,
    FOOD_TAJINE,
    FOOD_TANGIA,
    FOOD_TEA,
    FOOD_CROISSANT,
    FOOD_PASTILLA,
    FOOD_RFISSA,
    FOOD_COUNT
};

struct food {
    sf::RectangleShape Entity;
    std::string Name;
    bool bMoroccan;
    float VelocityY;
};

class Food
{
public:
    Food(sf::Vector2f windowSize);
    ~Food();

    void Add();
    void Update();
    void Draw(sf::RenderWindow &window);
    void checkCollision(Player &player, Hearts &hearts, Score &score);

    std::vector<struct food> food;
private:
    void loadTextures();
    
    float addInterval = 1.5f;

    sf::Clock clock;
    sf::Clock addClock;
    bool bIsMoroccan[FOOD_COUNT];
    std::string textureFiles[FOOD_COUNT];
    sf::Vector2f windowSize;
};