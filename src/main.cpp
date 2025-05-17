#include "player.h"
#include "platform.h"
#include "food.h"
#include "hearts.h"
#include "score.h"

int main()
{
    srand((unsigned) time(NULL));
    // -------------------------------------------------- INITIALIZATION ------------------------------------------------------------
        // ------- Window -------
    sf::Vector2f windowSize(1280.f, 720.f);
    const sf::Vector2f entitySize = sf::Vector2f(42.f, 64.f);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "GameProject");
    window.setFramerateLimit(60);

        // ------ Main Menu ------
    sf::Font font;
    sf::Text PlayButton;

    if (!font.loadFromFile("..\\..\\assets\\font\\dynamictrooper.ttf"))
        std::cout << "(-) Failed to load font" << std::endl;
    
    sf::Vector2i PlayButtonPos(sf::Vector2i(100, 50));
    PlayButton.setPosition(sf::Vector2f(PlayButtonPos));
    PlayButton.setCharacterSize(100);
    PlayButton.setFont(font);
    PlayButton.setFillColor(sf::Color::White);
    PlayButton.setStyle(sf::Text::Bold);
    PlayButton.setLetterSpacing(1.5f);
    PlayButton.setString("PLAY");
    bool bMainMenu = true;
    
        // ------- Player --------
    const float moveSpeed = 100.f;
    const float jumpForce = 400.f;
    
    Player player(window, entitySize, moveSpeed, jumpForce);
        // ------- Platforms -----
    Platform background("background.jpg", windowSize, sf::Vector2f(0.f, 0.f));
    Platform ground("ground.jpg", sf::Vector2f(windowSize.x, 175.f), sf::Vector2f(0.f, windowSize.y - 175.f));
    
    Hearts hearts(sf::Vector2f(400.f, 100.f), sf::Vector2f(windowSize.x - 450.f, windowSize.y - 140.f));
    Score score(font, sf::Vector2f(50.f, windowSize.y - 150.f));
        // ------ Food -----

    Food theFood(windowSize);

        // ----- CountDown Timer -----
    sf::Clock clock;
    sf::Text Timer;
    int remainingTime = 60;
    Timer.setPosition(sf::Vector2f(400.f, windowSize.y - 150.f));
    Timer.setCharacterSize(100);
    Timer.setFont(font);
    Timer.setOutlineColor(sf::Color::White);
    Timer.setOutlineThickness(4.f);
    Timer.setFillColor(sf::Color::Black);
    Timer.setStyle(sf::Text::Bold);
    Timer.setLetterSpacing(1.5f);
    Timer.setString("00:" + std::to_string(remainingTime));

    // ---------------------------------------------------- GAME LOOP -----------------------------------------------------------------
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {   
            if(event.type == sf::Event::Closed)
                window.close();
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !bMainMenu)
                bMainMenu = true;

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && player.collider.bCollidingWithGround) {
                player.Jump();
            }
        }
        
        // Load Main Menu
        if(bMainMenu)
        {
            // If Mouse position on play button.
            if(     sf::Mouse::getPosition(window).x >= PlayButtonPos.x && sf::Mouse::getPosition(window).x <= (PlayButtonPos.x + 200.f) &&
                    sf::Mouse::getPosition(window).y >= PlayButtonPos.y && sf::Mouse::getPosition(window).y <= (PlayButtonPos.y + 100.f)    )
            {
                PlayButton.setFillColor(sf::Color::Blue);
                    // Exit Main Menu
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    bMainMenu = false;
            } else
                PlayButton.setFillColor(sf::Color::White);
            
            // Clearing frame
            window.clear(sf::Color::Black);
            window.draw(PlayButton);
        }

        // Resume Game if Exited main menu
        else {
            // ------------------- ENTITIES --------------------
            player.Update();

            // Entity collision with other objects/entities.
            player.collider.checkCollision(ground.Entity);

            theFood.Add();
            theFood.Update();
            theFood.checkCollision(player, hearts, score);

            // ------------------- RENDER ----------------------
            // Clearing frame
            window.clear(sf::Color::Black);

            // Objects Render
            window.draw(background.Entity);
            window.draw(ground.Entity);
            window.draw(hearts.Entity);
            window.draw(score.Entity);
            window.draw(Timer);

            // Entity render  
            player.Draw();

            theFood.Draw(window);
            
            // ------------------- TIMER -----------------------
            if(clock.getElapsedTime().asSeconds() >= 1.0f && remainingTime > 0) {
                remainingTime--;
                clock.restart();
                
                if(remainingTime > 10)
                    Timer.setString("00:" + std::to_string(remainingTime));
                else
                    Timer.setString("00:0" + std::to_string(remainingTime));

                if(remainingTime <= 10)
                    Timer.setFillColor(sf::Color::Red);
            }
        }
        
        // Displaying frame.
        window.display();
    }

    return 0;
}