#include "player.h"
#include "platform.h"
#include "food.h"
#include "hearts.h"
#include "score.h"
#include "animation.h"

#define STARTING_TIMER 60

enum GAME_STATES {
    STATE_MAINSCREEN,
    STATE_PLAY,
    STATE_RESULTS
};

unsigned int remainingTime = STARTING_TIMER;
bool bLost = false;

void restartGame(Player &player, Food &food, Hearts &hearts, Score &score, sf::Text &Timer)
{
    bLost = false;
    player.resetPosition();
    hearts.Reset();
    score.Reset();
    food.food.clear();

    remainingTime = STARTING_TIMER;
    Timer.setString("00:" + std::to_string(remainingTime));
    Timer.setFillColor(sf::Color(255, 165, 0));
}

int main()
{
    // -------------------------------------------------- INITIALIZATION ------------------------------------------------------------
        // ------- Window -------
    sf::Vector2f windowSize(1280.f, 720.f);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "GameProject");
    window.setFramerateLimit(60);

    unsigned int iGameState = STATE_MAINSCREEN;
        // ------ Main Menu ------
    sf::Font font;
    sf::Text PlayButton;

    if(!font.loadFromFile("..\\..\\assets\\font\\dynamictrooper.ttf"))
        std::cout << "(-) Failed to load font" << std::endl;
    
    sf::Vector2i PlayButtonPos(sf::Vector2i((windowSize.x / 2) - 200, (windowSize.y/ 2) - 200));
    PlayButton.setPosition(sf::Vector2f(PlayButtonPos));
    PlayButton.setCharacterSize(200);
    PlayButton.setFont(font);
    PlayButton.setFillColor(sf::Color::Magenta);
    PlayButton.setStyle(sf::Text::Bold);
    PlayButton.setLetterSpacing(1.5f);
    PlayButton.setString("PLAY");

    sf::Text Credits;
    Credits.setPosition(sf::Vector2f(windowSize.x - 450.f, windowSize.y - 100.f));
    Credits.setCharacterSize(70);
    Credits.setFont(font);
    Credits.setFillColor(sf::Color::White);
    Credits.setLetterSpacing(1.5f);
    Credits.setString("Walid Abaaqil");
    
        // ------- Player --------
    const float scale = 2.0f;
    const float moveSpeed = 100.f;
    const float jumpForce = 400.f;
    const sf::Vector2f entitySize = sf::Vector2f(42.f, 64.f);

    Player player(window, entitySize * scale, scale, moveSpeed * scale, jumpForce);

        // -------- Dog ----------
    sf::Sprite Dog;
    Dog.setPosition(sf::Vector2f(windowSize.x - 150, windowSize.y - (175.f + 48.f * 2.0f)));
    Dog.setScale(sf::Vector2f(2.0f, 2.0f));

    Animation dogAnim;
    dogAnim.loadTextures(DOG_ANIMS);
    dogAnim.Set(DOG_BARK, 4, sf::Vector2u(48, 48));
    dogAnim.lookRight = false;

        // ------- Platforms -----
    Platform background("background.jpg", windowSize, sf::Vector2f(0.f, 0.f));
    Platform ground("ground.jpg", sf::Vector2f(windowSize.x, 175.f), sf::Vector2f(0.f, windowSize.y - 175.f));
    Platform info("info.png", sf::Vector2f(200.f, 200.f), sf::Vector2f((windowSize.x / 2) - 110.f, (windowSize.y / 2) + 100.f));
    Platform leftWall("", sf::Vector2f(10.f, windowSize.y - 175.f), sf::Vector2f(0.f, 0.f));
    Platform rightWall("", sf::Vector2f(10.f, windowSize.y - 175.f), sf::Vector2f(windowSize.x - 10.f, 0.f));
    Platform lost("lost.png", sf::Vector2f(487.5f, 391.5f), sf::Vector2f(40.f, (windowSize.y / 2) - 150.f));

    Hearts hearts(sf::Vector2f(400.f, 100.f), sf::Vector2f(windowSize.x - 385.f, windowSize.y - 140.f));
    Score score(font, sf::Vector2f(50.f, windowSize.y - 150.f));
    
        // ------ Food -----
    Food food(windowSize);

        // ----- CountDown Timer -----
    sf::Clock clock;
    sf::Clock deadClock;
    sf::Text Timer;
    Timer.setPosition(sf::Vector2f((windowSize.x / 2) - 150.f, windowSize.y - 150.f));
    Timer.setCharacterSize(100);
    Timer.setFont(font);
    Timer.setOutlineColor(sf::Color::Black);
    Timer.setOutlineThickness(4.f);
    Timer.setFillColor(sf::Color(255, 165, 0));
    Timer.setStyle(sf::Text::Bold);
    Timer.setLetterSpacing(1.5f);
    Timer.setString("00:" + std::to_string(remainingTime));

        // ------ Music & Sounds-------
    sf::Music music;
    if(!music.openFromFile("..\\..\\assets\\sound\\music.mp3"))
        std::cout << "(-) Failed to load music.mp3" << std::endl;
    else
        std::cout << "(+) Loaded music.mp3" << std::endl;
    
    music.setVolume(50.f);
    
    sf::SoundBuffer lostSoundBuffer;
    sf::Sound lostSound;
    if(lostSoundBuffer.loadFromFile("..\\..\\assets\\sound\\hchoma.wav")) {
        std::cout << "(+) Loaded sound hchoma.wav"<< std::endl;
        lostSound.setBuffer(lostSoundBuffer);
    } else
        std::cout << "(-) Failed to load sound hchoma.wav" << std::endl;
    
    sf::SoundBuffer winSoundBuffer;
    sf::Sound winSound;
    if(winSoundBuffer.loadFromFile("..\\..\\assets\\sound\\win.wav")) {
        std::cout << "(+) Loaded sound win.wav"<< std::endl;
        winSound.setBuffer(winSoundBuffer);
    } else
        std::cout << "(-) Failed to load sound win.wav" << std::endl;
    
        // ----- Results Screen ------
    sf::Text youLostText;
    youLostText.setPosition(sf::Vector2f(sf::Vector2i((windowSize.x / 2) - 100, (windowSize.y/ 2) - 100)));
    youLostText.setCharacterSize(180);
    youLostText.setFont(font);
    youLostText.setFillColor(sf::Color::Yellow);
    youLostText.setStyle(sf::Text::Bold);
    youLostText.setLetterSpacing(1.5f);
    youLostText.setString("YOU LOST!");

    sf::Text youWinText;
    youWinText.setPosition(sf::Vector2f(sf::Vector2i((windowSize.x / 2) - 310, (windowSize.y/ 2) - 125)));
    youWinText.setCharacterSize(180);
    youWinText.setFont(font);
    youWinText.setFillColor(sf::Color(255, 165, 0));
    youWinText.setStyle(sf::Text::Bold);
    youWinText.setLetterSpacing(1.5f);
    youWinText.setString("YOU LOST!");

    // ---------------------------------------------------- GAME LOOP -----------------------------------------------------------------
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {   
            if(event.type == sf::Event::Closed)
                window.close();
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && iGameState == STATE_PLAY)
                iGameState = STATE_MAINSCREEN;
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) /*&& iGameState == STATE_PLAY*/) {
                iGameState = STATE_PLAY; // REMOVE
                music.stop();
                music.play();
                restartGame(player, food, hearts, score, Timer);
            }
        }
        
        // Load Main Menu
        if(iGameState == STATE_MAINSCREEN) { 
            // If Mouse position on play button.
            if(     sf::Mouse::getPosition(window).x >= PlayButtonPos.x && sf::Mouse::getPosition(window).x <= (PlayButtonPos.x + 400.f) &&
                    sf::Mouse::getPosition(window).y >= PlayButtonPos.y && sf::Mouse::getPosition(window).y <= (PlayButtonPos.y + 200.f)    )
            {
                music.pause();
                PlayButton.setFillColor(sf::Color::Red);
                    // Exit Main Menu
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    iGameState = STATE_PLAY;
                    music.play();
                }
            } else
                PlayButton.setFillColor(sf::Color::Magenta);
            
            // Clearing frame
            window.clear(sf::Color::Black);
            window.draw(PlayButton);
            window.draw(Credits);
            window.draw(info.Entity);
        }

        else if(iGameState == STATE_RESULTS) {
            window.clear(sf::Color::Black);

            if(bLost) {
                window.draw(lost.Entity);
                window.draw(youLostText);
            } else {
                youWinText.setString("SCORE: " + std::to_string(score.iScore));
                window.draw(youWinText);
            }
        }

        // Resume Game if Exited main menu
        else if(iGameState == STATE_PLAY) {
            // ------------------- ENTITIES --------------------
            player.Update();

            // Entity collision with other objects/entities.
            player.collider.checkCollision(ground.Entity);
            player.collider.checkCollision(leftWall.Entity);
            player.collider.checkCollision(rightWall.Entity);

            food.Add();
            food.Update();
            food.checkCollision(player, hearts, score);

            dogAnim.Animate(Dog);

            // ------------------- RENDER ----------------------
            // Clearing frame
            window.clear(sf::Color::Black);

            // Objects Render
            window.draw(background.Entity);
            window.draw(ground.Entity);
            window.draw(leftWall.Entity);
            window.draw(rightWall.Entity);
            window.draw(hearts.Entity);
            window.draw(score.Entity);
            window.draw(Timer);

            // Entity render  
            player.Draw();

            food.Draw(window);

            window.draw(Dog);
            
            // ------------------- GAME LIFE -----------------------
            if(hearts.iHearts > 0) { // ------ ALIVE ------
                // ------ TIMER ------
                if(clock.getElapsedTime().asSeconds() >= 1.0f && remainingTime >= 0) {
                    if(remainingTime <= 0) {
                        iGameState = STATE_RESULTS;
                        winSound.play();
                        music.stop();
                    } else {
                        remainingTime--;
                        clock.restart();
                        
                        if(remainingTime >= 10)
                            Timer.setString("00:" + std::to_string(remainingTime));
                        else
                            Timer.setString("00:0" + std::to_string(remainingTime));

                        if(remainingTime <= 10)
                            Timer.setFillColor(sf::Color::Red);
                    }
                }
            } else { // ------ DEAD ------
                if(!player.Dead)
                    deadClock.restart();
                
                player.Dead = true;
                bLost = true;
                music.stop();
                if(deadClock.getElapsedTime().asSeconds() >= 2.0f) {
                    iGameState = STATE_RESULTS;
                    lostSound.play();
                    deadClock.restart();
                }
            }
        }
        
        // Displaying frame.
        window.display();
    }

    return 0;
}