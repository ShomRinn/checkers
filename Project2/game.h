#include "PlayerVsComputer.h"
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "EndMenu.h"
#include "ChoseTurn.h"

sf::RenderWindow window(sf::VideoMode(800, 800), "Checkers");
CheckersPvsC* Game = nullptr;

/// <summary>
/// функция запуска игры.
/// входные данные
///
/// </summary>

void BUILD()
{                                  // Restart button
    delete Game;
    Game = new CheckersPvsC(Turn); // send player side
    Game->SHOW();
    if (Game->GetPlayer() == 2)
    {
        Game->MakeAutoMove(1);
    }
}

sf::Sprite Map_Sprite;
sf::Sprite Checker_Sprite;
sf::Sprite Selection_Sprite;
/// <summary>
/// game UI visualisation
/// buttons(R,Escape) creatoin
/// </summary>
void startGame()
{
    sf::Image map_image;
    map_image.loadFromFile("images/map1.png");
    sf::Texture map;
    map.loadFromImage(map_image);
    Map_Sprite.setTexture(map);

    sf::Image white_image;
    white_image.loadFromFile("images/Checkers.PNG");
    sf::Texture white_texture;
    white_texture.loadFromImage(white_image);
    Checker_Sprite.setTexture(white_texture);

    sf::Image select_image;
    select_image.loadFromFile("images/Selection.png");
    sf::Texture select_texture;
    select_texture.loadFromImage(select_image);
    Selection_Sprite.setTexture(select_texture);
    Selection_Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

    menu(window);
    ChoseTurn(window);
    BUILD();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exit(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            return;
        }
        else
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                BUILD();
            }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.key.code == sf::Mouse::Left)
            {
                while (event.type != sf::Event::MouseButtonReleased)
                    window.pollEvent(event);

                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
                Pos tmp;

                tmp.y = pos.x / 100;

                tmp.x = pos.y / 100;

                if (Game->Click(tmp))
                {
                    if (Game->GetWinner() == Game->GetPlayer())
                    {
                        EndMenuWin(window);
                    }
                    else
                    {
                        EndMenuLose(window);
                    }
                    return;
                }
            }
        }
    }
}








