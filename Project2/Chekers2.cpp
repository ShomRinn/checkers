#include "Checkers.h"
#include <SFML/Graphics.hpp>
extern sf::RenderWindow window;
extern sf::Sprite Map_Sprite;
extern sf::Sprite Checker_Sprite;
extern sf::Sprite Selection_Sprite;

void ShowMap() //map creation
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
            {
                Map_Sprite.setTextureRect(sf::IntRect(100, 0, 100, 100));
            }
            else
            {
                Map_Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
            }
            Map_Sprite.setPosition(j * 100, i * 100);
            window.draw(Map_Sprite);
        }
    }
}

void ShowOneChecker(int x, int y, int player, bool king)  //checker creation
{
    if (player == 1 || player == 2)
    {
        Checker_Sprite.setTextureRect(sf::IntRect(king ? 100 : 0, (player - 1) * 100, 100, 100));
        Checker_Sprite.setPosition(x, y);
        window.draw(Checker_Sprite);
    }
}

int Reverse(int a, bool mirror, int base = 700)   //need for correct sprites creation(for each side)
{
    return (mirror ? (base - a) : a); // если миро истинно, то возвр base-a, иначе возвр а
}

void Checkers::SHOW() {  //game 
    window.clear();

    ShowMap();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            ShowOneChecker(Reverse(j * 100, Mirror), Reverse(i * 100, Mirror), ((Field[i][j].Fake ? (1 + 2 - Field[i][j].Color) : Field[i][j].Color)), Field[i][j].King);
        }
    }

    window.display();
}

void Checkers::SELECT(Pos p) {  //map selection
    window.clear();

    ShowMap();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            ShowOneChecker(Reverse(j * 100, Mirror), Reverse(i * 100, Mirror), ((Field[i][j].Fake ? (1 + 2 - Field[i][j].Color) : Field[i][j].Color)), Field[i][j].King);
        }
    }

    Selection_Sprite.setPosition(Reverse(p.y * 100, Mirror), Reverse(p.x * 100, Mirror));
    window.draw(Selection_Sprite);

    window.display();
}

void Checkers::MOVE(Pos p, Pos pNew) {  //checker movement graphics

    sf::Clock clock;
    int ms = clock.getElapsedTime().asMilliseconds();
    const int MS = 500;

    while (ms < MS) 
    {
        window.clear();

        ShowMap();

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (Pos(i, j) != p)
                {
                    ShowOneChecker(Reverse(j * 100, Mirror), Reverse(i * 100, Mirror), ((Field[i][j].Fake ? (1 + 2 - Field[i][j].Color) : Field[i][j].Color)), Field[i][j].King);
                }
            }
        }

        int dx = (pNew.x - p.x) * 100, dy = (pNew.y - p.y) * 100;
        ShowOneChecker(Reverse(p.y * 100 + dy * ms / MS, Mirror), Reverse(p.x * 100 + dx * ms / MS, Mirror), Field[p].Color, Field[p].King);

        window.display();
        ms = clock.getElapsedTime().asMilliseconds();
    }

}