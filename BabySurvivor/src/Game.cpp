#include "Game.h"

Game::Game() 
	: gameWindow(sf::VideoMode(1000, 700), "BabySurvivor")
{
	gameWindow.setFramerateLimit(60);
}

void Game::display()
{

	sf::CircleShape testShape(10);
	testShape.setPosition(500, 350);

	while (gameWindow.isOpen()) 
	{
		sf::Event event;
		while (gameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) { gameWindow.close(); }
			if (event.type == sf::Event::Resized) 
			{
				sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
				gameWindow.setView(sf::View(visibleArea));
			}
		}

		gameWindow.clear(sf::Color::Black);
		gameWindow.draw(testShape);
		gameWindow.display();
	}
}

int runGame() {
	Game game;
	game.display();
	return 1;
}