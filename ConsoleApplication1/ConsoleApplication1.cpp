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
    sf::RenderWindow window(sf::VideoMode(1820, 1024), "AiRrcherito", sf::Style::Close | sf::Style::None); //renderuję okno, nadaję początkowe parametry, jak wielkość okna czy tytuł, ustalam styl okna, czyli np. szerokość, wysokość, czy posiada pasek tytułowy, czy jest podatny na modyfikacje etc.
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(700.0f, 384.0f));
    sf::RectangleShape endbox(sf::Vector2f(290.f, 400.f));


    //Czcionka, menu
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        throw("couldnt load the font");
    sf::Text mejnmenju;
    sf::Text option1;
    sf::Text option2;
    sf::Text option3;
    mejnmenju.setFont(font);
    mejnmenju.setString("AiRcherito");
    mejnmenju.setCharacterSize(120);
    mejnmenju.setFillColor(sf::Color::Cyan);
    mejnmenju.setPosition(sf::Vector2f(220.0f, 50.0f));
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
    option3.setPosition(sf::Vector2f(500.0f, 650.0f));

    int option = 1;
    bool in_menu = true;
    bool good = true;

    //Nadaje tekstury obiektom
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Playersprite.png");
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("background.png");
    sf::Texture background2Texture;
    background2Texture.loadFromFile("background2.png");
    sf::Texture platformTexture;
    platformTexture.loadFromFile("floor.png");
    sf::Texture endboxTexture;
    endboxTexture.loadFromFile("endingbox.jpg");
    sf::Texture monsterTexture;
    monsterTexture.loadFromFile("monster.png");

    Player background2(&background2Texture, sf::Vector2u(1, 1), 0.3f, 100.0f, 200.0f);
    Player background(&backgroundTexture, sf::Vector2u(1, 1), 0.3f, 60.0f, 200.0f);
    Player player(&playerTexture, sf::Vector2u(8, 6), 0.1f, 200.0f, 300.0f);
    Player updateB3(&endboxTexture, sf::Vector2u(1, 1), 0.1f, 0.0f, 0.0f);
    std::vector<Enemy> enemies;
    enemies.push_back(Enemy(&monsterTexture, sf::Vector2f(200.0f, 128.0f)));

    //Tworze wektor by skrocic kod, w tym miejscu wystarczy ctrl+c, ctrl+v, a przy renderowaniu operacje warunkowe
    std::vector<Platform> platforms;

    platforms.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(700.0f, -1150.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(515.0f, -860.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(500.0f, -570.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(900.0f, -280.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(700.0f, 10.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(500.0f, 300.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(2000.0f, 200.0f), sf::Vector2f(500.0f, 600.0f)));
    platforms.push_back(Platform(&endboxTexture, sf::Vector2f(200.0f, 145.0f), sf::Vector2f(700.0f, -1400.0f)));

        sf::Music music;
        if (!music.openFromFile("mjuzik.wav"))
            return -1;
        music.setVolume(0.f);
        music.play();


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
                        if (option != 3) {
                            std::cout << "Wybrano opcje " << option << std::endl;
                        }
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
            
        }
        else {
            if (option == 1) {
                // "odswiezam" klatki
            
                player.update(deltaTime);
                background.updateB(deltaTime);
                background2.updateB2(deltaTime);
                for (Enemy& enemy : enemies)
                    enemy.Draw(window);

                sf::Vector2f direction;



                for (Platform& platform : platforms)
                    if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
                        player.OnCollision(direction);
                /*
                int enemyindex = 0;
                for (Enemy& enemy : enemies)
                {
                    if (enemy.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
                    {
                        enemies.erase();
                    }
                    */
                std::vector<Enemy>::iterator destroyIndex = nullptr;
                    for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++) {
                            if (it->GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
                            {
                                destroyIndex = it;
                            }
                    }
                    //enemyindex++;
                //}
                    enemies.erase(destroyIndex);

                    view.setCenter(player.GetPosition());

                //window.clear usuwa poprzednie klatki poruszającego się obiektu
                window.clear();
                window.setView(view);
                background.Draw(window);
                background2.Draw(window);
                player.Draw(window); //rysowanie postaci
                for (Platform& platform : platforms)
                    platform.Draw(window);
                for (Enemy& enemy : enemies)
                    enemy.Draw(window);
                if (evnt.key.code == sf::Keyboard::Escape) {
                    if (in_menu) {
                        option = 3;
                        in_menu = false;
                    }
                }

            }
            if (option == 2) {
                sf::Text inst;
                inst.setFont(font);
                inst.setString("To move the character to the left (<) push A button\n To the right (>) its needed to be pushed the D button\n To jump the space (_) must be pressed");
                inst.setCharacterSize(60);
                inst.setFillColor(sf::Color::White);
                inst.setPosition(sf::Vector2f(200.0, 500.0));
                window.draw(inst);
                if (evnt.key.code == sf::Keyboard::Escape) {
                    if (in_menu) {
                        option = 3;
                        in_menu = false;
                    }
                }
            }
            if (option == 3) {
                window.close();
            }
        }
        window.display();
        window.clear();

    }
}
