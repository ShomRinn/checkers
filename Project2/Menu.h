/// <summary>
/// start Menu cteation
///  start Menu  buttons
/// </summary>
void menu(sf::RenderWindow& window) {  
    sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground, EndMenuTexture1, AboutMenuTexture, AboutTexture;
    menuTexture1.loadFromFile("images/NewGame.png");
    menuTexture2.loadFromFile("images/Rules.png");
    menuTexture3.loadFromFile("images/Exit.png");
    aboutTexture.loadFromFile("images/Rules.jpg");
    menuBackground.loadFromFile("images/Penguins.jpg");
    EndMenuTexture1.loadFromFile("images/ExitToMenu.png");
    AboutMenuTexture.loadFromFile("images/About.jpg");
    AboutTexture.loadFromFile("images/About.png");
    sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground), ExMen(EndMenuTexture1), AboutMenu(AboutMenuTexture), About(AboutTexture);

    menu1.setPosition(120, 230);
    menu2.setPosition(120, 290);
    About.setPosition(120, 350);
    menu3.setPosition(120, 410);
    menuBg.setPosition(0, 0);

    while (true)
    {
        sf::Event event;

        while (window.pollEvent(event))   //check
        {
            if (event.type == sf::Event::MouseButtonPressed)
                break;
        }

        window.clear(sf::Color(129, 181, 221));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (sf::IntRect(200, 230, 300, 50).contains(sf::Mouse::getPosition(window))) //button creation 
            {
                break;
            }
            else
                if (sf::IntRect(200, 290, 300, 50).contains(sf::Mouse::getPosition(window)))
                {
                    window.draw(about);
                    ExMen.setPosition(200, 700);
                    window.draw(ExMen);
                    window.display();
                    while (true)
                    {
                        if (window.pollEvent(event))
                        {
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                if (sf::IntRect(200, 700, 300, 50).contains(sf::Mouse::getPosition(window)))
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                    if (sf::IntRect(200, 350, 300, 50).contains(sf::Mouse::getPosition(window)))
                    {
                        window.draw(AboutMenu);
                        ExMen.setPosition(200, 700);
                        window.draw(ExMen);
                        window.display();
                        while (true)
                        {
                            if (window.pollEvent(event))
                            {
                                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                                {
                                    if (sf::IntRect(200, 700, 300, 50).contains(sf::Mouse::getPosition(window)))
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else
                        if (sf::IntRect(200, 410, 300, 50).contains(sf::Mouse::getPosition(window)))
                        {
                            exit(0);
                        }
        }

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(About);
        window.draw(menu3);

        window.display();
    }
}