/// <summary>
/// Win End menu UI creation
/// </summary>
void EndMenuWin(sf::RenderWindow& window)
{
	sf::Texture EndMenuTexture1, EndMenuTexture3;
	EndMenuTexture1.loadFromFile("images/ExitToMenu.JPEG");
	EndMenuTexture3.loadFromFile("images/WinMenu.jpg");
	sf::Sprite ExitToMenu(EndMenuTexture1), WinMenu(EndMenuTexture3);

	ExitToMenu.setPosition(200, 330);
	WinMenu.setPosition(0, 0);

    while (true)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
                break;
        }

        window.clear(sf::Color(129, 181, 221));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

              if (sf::IntRect(200, 330, 300, 100).contains(sf::Mouse::getPosition(window)))
              {
                   break;
              }
        }

        window.draw(WinMenu);
        window.draw(ExitToMenu);

        window.display();
    }
}
/// <summary>
/// Lose End menu UI creation
/// </summary>
void EndMenuLose(sf::RenderWindow& window)
{
    sf::Texture EndMenuTexture1, EndMenuTexture3;
    EndMenuTexture1.loadFromFile("images/ExitToMenu.png");
    EndMenuTexture3.loadFromFile("images/LoseMenu.jpg");
    sf::Sprite ExitToMenu(EndMenuTexture1), WinMenu(EndMenuTexture3);

    ExitToMenu.setPosition(200, 330);
    WinMenu.setPosition(0, 0);

    while (true)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
                break;
        }

        window.clear(sf::Color(129, 181, 221));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
                if (sf::IntRect(200, 330, 300, 100).contains(sf::Mouse::getPosition(window)))
                {
                    break;
                }
        }

        window.draw(WinMenu);
        window.draw(ExitToMenu);

        window.display();
    }
}
