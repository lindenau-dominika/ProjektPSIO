#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "player.h"
#include "Enemy.h"
#include "Platform.h"
#include "Collider.h"
#include <vector>
#include <fstream>
#include <string>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1820, 1024), "AiRrcherito", sf::Style::Close | sf::Style::Fullscreen); //renderuję okno, nadaję początkowe parametry, jak wielkość okna czy tytuł, ustalam styl okna, czyli np. szerokość, wysokość, czy posiada pasek tytułowy, czy jest podatny na modyfikacje etc.
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(700.0f, 384.0f));
    sf::RectangleShape endbox(sf::Vector2f(2000.0f, 2000.f));
    sf::RectangleShape meme(sf::Vector2f(1000.f, 300.f));
    sf::RectangleShape door(sf::Vector2f(200.f, 220.f));
    sf::RectangleShape bckground(sf::Vector2f(5000.f, 5000.f));
    meme.setPosition(-800.0, 1000.0);
    door.setPosition(-1020.0, 1080.0);
    
    bckground.setPosition(-2500, -1800);

    //Czcionka, menu
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        throw("couldnt load the font");
    sf::Text mejnmenju;
    sf::Text option1;
    sf::Text option2;
    sf::Text option3;
    sf::Text option4;
    sf::Text napis;
    sf::Text napis1;
    

    mejnmenju.setFont(font);
    mejnmenju.setString("AiRcherito");
    mejnmenju.setCharacterSize(120);
    mejnmenju.setFillColor(sf::Color::Cyan);
    mejnmenju.setPosition(sf::Vector2f(220.0f, 50.0f));

    napis.setFont(font);
    napis.setString("Hmm u must have missed a coin :/ \ncheck on the left just behind the tree!");
    napis.setCharacterSize(10);
    napis.setFillColor(sf::Color::White);
    napis.setPosition(sf::Vector2f(500.f, -1320.f));
    
    napis1.setFont(font);
    napis1.setString("music and graphics (except The Ugandan Knuckles meme) made by the creator of this game");
    napis1.setCharacterSize(30);
    napis1.setFillColor(sf::Color::White);
    napis1.setPosition(sf::Vector2f(400.f, 1000.f));
    
    option1.setFont(font);
    option1.setString("Play");
    option1.setCharacterSize(90);
    option1.setFillColor(sf::Color::Cyan);
    option1.setPosition(sf::Vector2f(300.0f, 250.0f));
    
    option2.setFont(font);
    option2.setString("How to play?");
    option2.setCharacterSize(90);
    option2.setFillColor(sf::Color::Cyan);
    option2.setPosition(sf::Vector2f(400.0f, 450.0f));
    
    option3.setFont(font);
    option3.setString("Exito see you laterito");
    option3.setCharacterSize(90);
    option3.setFillColor(sf::Color::Cyan);
    option3.setPosition(sf::Vector2f(600.0f, 650.0f));

    int z = 3;
    int c = 0;
    sf::Text hp;
    hp.setFont(font);
    hp.setCharacterSize(24);
    hp.setFillColor(sf::Color::Cyan);
    hp.setStyle(sf::Text::Bold);
    hp.setString(std::to_string(z));
    sf::Text coin;
    coin.setFont(font);
    coin.setCharacterSize(24);
    coin.setFillColor(sf::Color::Cyan);
    coin.setStyle(sf::Text::Bold);
    coin.setString(std::to_string(c));

    sf::Text zycie;
    zycie.setFont(font);
    zycie.setCharacterSize(24);
    zycie.setFillColor(sf::Color::Cyan);
    zycie.setStyle(sf::Text::Bold);
    zycie.setString("Health Points:");
    sf::Text money;
    money.setFont(font);
    money.setCharacterSize(24);
    money.setFillColor(sf::Color::Cyan);
    money.setStyle(sf::Text::Bold);
    money.setString("Coins:");
    sf::Text money1;
    money1.setFont(font);
    money1.setCharacterSize(24);
    money1.setFillColor(sf::Color::Cyan);
    money1.setStyle(sf::Text::Bold);
    money1.setString("/4");


    int option = 1;
    bool in_menu = true;
    bool good = true;
    

    //Nadaje tekstury obiektom
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Playersprite.png");
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("sky.png");
    sf::Texture background2Texture;
    background2Texture.loadFromFile("background2.png");
    sf::Texture platformTexture;
    platformTexture.loadFromFile("floor.png");
    sf::Texture endboxTexture;
    endboxTexture.loadFromFile("endboxinio.png");
    sf::Texture mTexture;
    mTexture.loadFromFile("enemo.png");
    sf::Texture blockTexture;
    blockTexture.loadFromFile("trreee2.png");
    sf::Texture memeTexture;
    memeTexture.loadFromFile("tenor.gif");
    sf::Texture coinTexture;
    coinTexture.loadFromFile("coin.png");
    sf::Texture doorTexture;
    doorTexture.loadFromFile("doors.png");
    door.setTexture(&doorTexture);
    meme.setTexture(&memeTexture);
    endbox.setTexture(&endboxTexture);
    bckground.setTexture(&backgroundTexture);
    Player background2(&background2Texture, sf::Vector2u(1, 1), 0.3f, 100.0f, 200.0f);
    //Player background(&backgroundTexture, sf::Vector2u(1, 1), 0.3f, 0.0f, 200.0f);
    Player player(&playerTexture, sf::Vector2u(8, 6), 0.1f, 200.0f, 300.0f);
    Player updateB3(&endboxTexture, sf::Vector2u(1, 1), 0.1f, 0.0f, 0.0f);

    Enemy monster(&mTexture, sf::Vector2f(640.0f, -930.0f), 60.0f, sf::Vector2u(8, 1), 0.03f);
    Enemy monster1(&mTexture, sf::Vector2f(650.0f, -640.0f), 50.0f, sf::Vector2u(8, 1), 0.03f);
    Enemy monster2(&mTexture, sf::Vector2f(1000.0f, -60.0f), 70.0f, sf::Vector2u(8, 1), 0.03f);
    Enemy monster3(&mTexture, sf::Vector2f(650.0f, 230.0f), 90.0f, sf::Vector2u(8, 1), 0.03f);
    Enemy coino(&coinTexture, sf::Vector2f(650.0f, 230.0f), 0.0f, sf::Vector2u(13, 1), 0.03f);
    Enemy coino1(&coinTexture, sf::Vector2f(-700.f, 1200.f), 0.0f, sf::Vector2u(13, 1), 0.03f);
    Enemy coino2(&coinTexture, sf::Vector2f(650.0f, -640.0f), 0.0f, sf::Vector2u(13, 1), 0.03f);
    Enemy coino3(&coinTexture, sf::Vector2f(850.0f, -60.0f), 0.0f, sf::Vector2u(13, 1), 0.03f);
    
   // std::vector<Enemy> enemies;
    /*enemies.push_back(Enemy(&mTexture, sf::Vector2f(200.0f, 128.0f), 100.0f));
    enemies.push_back(Enemy(&mTexture, sf::Vector2f(200.0f, 228.0f), 100.0f));*/

    //Tworze wektor by skrocic kod, w tym miejscu wystarczy ctrl+c, ctrl+v, a przy renderowaniu operacje warunkowe
    std::vector<Platform> platforms;

    platforms.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(700.0f, -1150.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(515.0f, -860.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(500.0f, 100.0f), sf::Vector2f(420.0f, -570.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(900.0f, -280.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(700.0f, 10.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(500.0f, 300.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(2000.0f, 200.0f), sf::Vector2f(500.0f, 600.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(2000.0f, 200.0f), sf::Vector2f(-600.0f, 1400.0f)));
    platforms.push_back(Platform(&blockTexture, sf::Vector2f(300.0f, 450.0f), sf::Vector2f(1400.0f, 360.0f)));
    platforms.push_back(Platform(&blockTexture, sf::Vector2f(300.0f, 300.0f), sf::Vector2f(-360.0f, 395.0f)));
    platforms.push_back(Platform(&blockTexture, sf::Vector2f(300.0f, 400.0f), sf::Vector2f(100.0f, 1150.0f)));
    
    //platforms.push_back(Platform(&endboxTexture, sf::Vector2f(200.0f, 145.0f), sf::Vector2f(700.0f, -1400.0f)));

        sf::Music music;
        if (!music.openFromFile("mjuzik.wav"))
            return -1;
        music.setVolume(60.f);
        music.play();
        music.setLoop(true);


    float deltaTime = 0.0f;
    sf::Clock clock;

    //operacje warunkowe które decydują o tym co dzieje się, kiedy okno aplikacji jest otwarte
    while (window.isOpen())
    {
        //deltaTime dostosowuje predkosc aplikacji do parametrow komputera
        deltaTime = clock.restart().asSeconds();
        //sf::Event evnt umozliwia przemieszczanie okna
       
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == evnt.Closed)
                window.close();

            if (evnt.type == evnt.KeyPressed) {
                if (good) {
                    if (evnt.key.code == sf::Keyboard::Down) {
                        if (option < 3) {
                            option += 1;
                        }
                    }
                    if (evnt.key.code == sf::Keyboard::Up) {
                        if (option > 1) {
                            option -= 1;
                        }
                    }
                    if (evnt.key.code == sf::Keyboard::Enter or evnt.key.code == sf::Keyboard::Space) {
                        in_menu = false;
                        
                    }
                    good = false;
                }
                if (evnt.key.code == sf::Keyboard::Escape) {
                    if (in_menu) {
                        option = 3;
                        in_menu = false;
                    }
                    else if (!in_menu) {
                        option = 1;
                        in_menu = true;
                    }

                }
            }
            if (evnt.type == evnt.KeyReleased) {
                good = true;
            }
        }
        if (in_menu) {

            if (option == 1)
            {
                option1.setFillColor(sf::Color::White);
                option1.setCharacterSize(100);
                option2.setFillColor(sf::Color::Cyan);
                option2.setCharacterSize(90);
                option3.setFillColor(sf::Color::Cyan);
                option3.setCharacterSize(90);
                
            }
            if (option == 2)
            {
                option1.setFillColor(sf::Color::Cyan);
                option1.setCharacterSize(90);
                option2.setFillColor(sf::Color::White);
                option2.setCharacterSize(100);
                option3.setFillColor(sf::Color::Cyan);
                option3.setCharacterSize(90);
                
            }
            if (option == 3)
            {
                option1.setFillColor(sf::Color::Cyan);
                option1.setCharacterSize(90);
                option2.setFillColor(sf::Color::Cyan);
                option2.setCharacterSize(90);
                option3.setFillColor(sf::Color::White);
                option3.setCharacterSize(100);
                
            }
            window.draw(mejnmenju);
            window.draw(option1);
            window.draw(option2);
            window.draw(option3);
            window.draw(napis1);
            
            
        }
        else {
            if (option == 1) {
                
                // "odswiezam" klatki
                window.clear();
                window.setView(view);
                
                //background.Draw(window);
                window.draw(bckground);
                window.draw(meme);
                background2.Draw(window);
                for (Platform& platform : platforms)
                    platform.Draw(window);
                
                player.Draw(window);
                window.draw(door);
                
                

                sf::Vector2f direction;

                for (Platform& platform : platforms)
                    if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
                    {
                        player.OnCollision(direction);
                    }
                player.update(deltaTime);
                //background.updateB(deltaTime);
                background2.updateB2(deltaTime);
                
                if (monster.getExists())
                {   
                   
                    monster.update1(deltaTime);
                    

                    if (player.getBounds().intersects(monster.getBounds()))
                    {
                        monster.kill();
                        z--;

                    }
                     
                    monster.Draw(window);
                }

                
                if (monster1.getExists())
                {
                    monster1.update2(deltaTime);

                    if (player.getBounds().intersects(monster1.getBounds()))
                    {
                        monster1.kill();
                        z--;

                    }
                    monster1.Draw(window);

                }
                if (monster2.getExists())
                {
                    monster2.update3(deltaTime);

                    if (player.getBounds().intersects(monster2.getBounds()))
                    {
                        monster2.kill();
                        z--;

                    }
                    monster2.Draw(window);

                }
                if (monster3.getExists())
                {
                    monster3.update4(deltaTime);

                    if (player.getBounds().intersects(monster3.getBounds()))
                    {
                        monster3.kill();
                        z--;

                    }
                    monster3.Draw(window);

                }
                if (coino.getExists())
                {

                    coino.update1(deltaTime);


                    if (player.getBounds().intersects(coino.getBounds()))
                    {
                        coino.kill();
                        c++;

                    }

                    coino.Draw(window);
                }
                if (coino1.getExists())
                {

                    coino1.update1(deltaTime);


                    if (player.getBounds().intersects(coino1.getBounds()))
                    {
                        coino1.kill();
                        c++;

                    }

                    coino1.Draw(window);
                }
                if (coino2.getExists())
                {

                    coino2.update1(deltaTime);


                    if (player.getBounds().intersects(coino2.getBounds()))
                    {
                        coino2.kill();
                        c++;

                    }

                    coino2.Draw(window);
                }
                if (coino3.getExists())
                {

                    coino3.update1(deltaTime);


                    if (player.getBounds().intersects(coino3.getBounds()))
                    {
                        coino3.kill();
                        c++;

                    }

                    coino3.Draw(window);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                    window.close();
                }
                if (z == 0)
                {
                    window.close();
                }
                if (player.GetPosition().y <= -1180 && player.GetPosition().x > 600 && c==4)
                {  
                    endbox.setPosition(player.GetPosition().x-700, player.GetPosition().y - 800);
                    window.draw(endbox);
                }
                if (player.GetPosition().y <= -1180 && player.GetPosition().x > 500 && c < 4)
                {   
                    window.draw(napis);
                }
                if (player.GetPosition().y <= -1400 && player.GetPosition().x > 100 && c==4)
                {
                    window.close();
                }
                
               

                    view.setCenter(player.GetPosition());
                    hp.setPosition(player.GetPosition().x - 130.0f, player.GetPosition().y + 140.f);
                    coin.setPosition(player.GetPosition().x + 180.0f, player.GetPosition().y + 140.f);
                    money.setPosition(player.GetPosition().x + 100.0f, player.GetPosition().y + 140.f);
                    money1.setPosition(player.GetPosition().x + 200.0f, player.GetPosition().y + 140.f);
                    zycie.setPosition(player.GetPosition().x - 310.0f, player.GetPosition().y + 140.f);
               
                    

                window.draw(hp);
                window.draw(money);
                window.draw(money1);
                window.draw(coin);
                window.draw(zycie);
                
                

            }
            if (option == 2) {
                sf::Text inst;
                inst.setFont(font);
                inst.setString("To move the character to the left (<) push the A button\n To the right (>) push the D button\n To jump push the space button (_)\n You are not capable of killing enemies so do your best \nto avoid them!!! :)");
                inst.setCharacterSize(60);
                inst.setFillColor(sf::Color::White);
                inst.setPosition(sf::Vector2f(200.0, 400.0));
                window.draw(inst);
                
            }
            
           
            if (option == 3) {
                window.close();
            }
        }
        hp.setString(std::to_string(z));
        coin.setString(std::to_string(c));
        
        
        
        
        window.display();
        window.clear();

    }
}
