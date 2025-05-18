#include <iostream>
#include <chrono>
#include "food.h"
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

std::string g_foodNames[FOOD_COUNT] = {
    "baghrir",
    "chebakia",
    "couscous",
    "tajine",
    "tangia",
    "tea",
    "kebab",
    "noodles",
    "pizza",
    "spaghetti"
};

sf::Texture g_FoodTextures[FOOD_COUNT];

bool g_bMoroccan[FOOD_COUNT] = {
    true,
    true,
    true,
    true,
    true,
    true,
    false,
    false,
    false,
    false
};

Food::Food(sf::Vector2f windowSize) :
    windowSize(windowSize)
{
    loadTextures();
}

Food::~Food()
{
}

void Food::Add()
{
    if(addClock.getElapsedTime().asSeconds() < addInterval)
        return;
    
    addClock.restart();

    struct food added_food;

    std::uniform_int_distribution<> dist1(0, FOOD_COUNT - 1);
    int randomNum = dist1(gen);
    added_food.bMoroccan = g_bMoroccan[randomNum];
    added_food.Entity.setTexture(&g_FoodTextures[randomNum]);
    added_food.Name.assign(g_foodNames[randomNum]);

    std::uniform_int_distribution<> dist2(200, int(windowSize.x) - (250 + FOOD_SIZE_X));
    int secRandomNum = dist2(gen);
    added_food.Entity.setPosition(secRandomNum, 0.f);
    added_food.Entity.setSize(sf::Vector2f(FOOD_SIZE_X, FOOD_SIZE_Y));

    food.push_back(added_food);

    std::cout << "(*) Generated Food " << g_foodNames[randomNum] << ", Moroccan: " << (g_bMoroccan[randomNum] ? "true" : "false") << ", POS_X: " << std::to_string(secRandomNum) << std::endl;
}

void Food::checkCollision(Player &player, Hearts &hearts, Score &score)
{
    for(int i = 0; i < food.size(); i++) {
        if(player.collider.checkCollision(food.at(i).Entity)) {
            if(food.at(i).bMoroccan) {
                score.incScore();
                std::cout << "(*) +1 Score " << food.at(i).Name << std::endl;
            } else {
                hearts.decHearts();
                std::cout << "(*) -1 Heart " << food.at(i).Name << std::endl;
            }

            food.at(i).Entity.setFillColor(sf::Color::Transparent);
            food.erase(food.begin() + i);
        }
    }
}

void Food::Draw(sf::RenderWindow &window)
{
    for(int i = 0; i < food.size(); i++)
        window.draw(food.at(i).Entity);
}

void Food::Update()
{
    double deltaTime = clock.restart().asSeconds();

    for(int i = 0; i < food.size(); i++)
        food.at(i).Entity.move(0.f, 1.75f);
}

void Food::loadTextures()
{
    for(int i = 0; i < FOOD_COUNT; i++) {
        if(g_FoodTextures[i].loadFromFile("..\\..\\assets\\textures\\food\\" + g_foodNames[i] + ".png"))
            std::cout << "(+) Loaded " << g_foodNames[i] << " texture." << std::endl;
        else
            std::cout << "(-) Failed to load " << g_foodNames[i] << " texture." << std::endl;
    }
}