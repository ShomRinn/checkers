int Turn;

void ChoseTurn(sf::RenderWindow& window)
{
    sf::Texture ChoseTurnTexture, TurnWhiteTexture, TurnBlackTexture, MenuForTurnTexture, MenuForTurnTexture2;
    MenuForTurnTexture2.loadFromFile("images/ChoseMenu2.jpg");
    MenuForTurnTexture.loadFromFile("images/MenuForTurn.png");
    ChoseTurnTexture.loadFromFile("images/ChoseTurn.png");
    TurnWhiteTexture.loadFromFile("images/TurnWhite.png");
    TurnBlackTexture.loadFromFile("images/TurnBlack.png");
    sf::Sprite ChoseTurn(ChoseTurnTexture), TurnWhite(TurnWhiteTexture), TurnBlack(TurnBlackTexture), MenuForTurn(MenuForTurnTexture), MenuForTurn2(MenuForTurnTexture2);

    MenuForTurn2.setPosition(0, 0);
    MenuForTurn.setPosition(200, 275);
    ChoseTurn.setPosition(225, 300);
    TurnWhite.setPosition(340, 375);
    TurnBlack.setPosition(325, 450);



/// <summary>
/// Chose Turn UI
///     check
///     button creation
/// </summary>
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
            if (sf::IntRect(340, 375, 250, 50).contains(sf::Mouse::getPosition(window)))
            {
                Turn = 1;
                break;
            }
            else
                if (sf::IntRect(325, 450, 250, 50).contains(sf::Mouse::getPosition(window)))
                {
                    Turn = 2;
                    break;
                }
        }

        window.draw(MenuForTurn2);
        window.draw(MenuForTurn);
        window.draw(ChoseTurn);
        window.draw(TurnWhite);
        window.draw(TurnBlack);
        window.display();
    }
}