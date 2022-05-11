#include <SFML/Graphics.hpp>
#include "GameHandler.h"
#include <iostream>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	sf::Image icon;
	icon.loadFromFile("../Resources/images/icon.png");
	sf::RenderWindow gameWindow(sf::VideoMode(600, 600), "Space Invaders", sf::Style::Titlebar | sf::Style::Close);
	
	gameWindow.setFramerateLimit(200);
	gameWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::Event event;
	sf::Clock gameTime;
	
	GameHandler *game;
	game = new GameHandler(static_cast <float> (gameWindow.getSize().x), static_cast <float> (gameWindow.getSize().y));

	while (gameWindow.isOpen())
	{
		while (gameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				gameWindow.close();
			}

			if (event.type == sf::Event::KeyReleased && game->getState() == -1)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					game->getMenuPtr().moveUp();
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					game->getMenuPtr().moveDown();
				}
				else if (event.key.code == sf::Keyboard::Return)
				{
					game->setState(game->getMenuPtr().menuSelect());
				}
			}
		}

		if (game->getState() == 2)
		{
			gameWindow.close();
		}
		
		game->Update(gameTime.restart().asSeconds());

		gameWindow.clear();
		gameWindow.draw(*game);
		gameWindow.display();
	}

	delete game;
	return 0;
}