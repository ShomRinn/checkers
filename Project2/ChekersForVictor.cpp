#include"game.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>

/// <summary>
/// main game cycle
/// </summary>
int main()
{    
    ShowWindow(GetConsoleWindow(), 0);

    for (;;)
    {
        startGame();
    }

    return 0;
}