#include "Game.h"
#include "StringHelpers.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() 
{
	font.loadFromFile("resources/Sansation.ttf");
	statsText.setFont(font);
	statsText.setPosition(5.f, 5.f);
	statsText.setCharacterSize(10);
}

int runGame() {
	Game game;
	game.run();
	return 1;
}

void Game::processEvent() 
{
	sf::Event event{ sf::Event::Count };

	while (gameWindow.pollEvent(event))
	{
		switch (event.type) 
		{
			case sf::Event::Closed:
				gameWindow.close();
				break;

			case sf::Event::Resized: {
				sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
				gameWindow.setView(sf::View(visibleArea));
			}
				
			default:
				break;
		}
		
	}
}

void Game::update(sf::Time elapsedTime)
{
	// All the logic will take place here
}

void Game::render() 
{
	gameWindow.clear(sf::Color::Black);

	sf::CircleShape testShape(10);
	testShape.setPosition(500, 350);

	gameWindow.draw(testShape);

	gameWindow.draw(statsText);
	gameWindow.display();
}

void Game::updateStats(sf::Time elapsedTime)
{
	statsUpdateTime += elapsedTime;
	numFrames += 1;

	if (statsUpdateTime >= sf::seconds(1.0f))
	{
		statsText.setString(
			"Frames / Seconds = " + toString(numFrames) + "\n" +
			"Time / Update = " + toString(statsUpdateTime.asMicroseconds() / numFrames) + "us"
		);

		statsUpdateTime -= sf::seconds(1.0f);
		numFrames = 0;
	}
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	gameWindow.setFramerateLimit(60);

	while (gameWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvent();
			update(TimePerFrame);
		}

		updateStats(elapsedTime);
		render();
	}
}