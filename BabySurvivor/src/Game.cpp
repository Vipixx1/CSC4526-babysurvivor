#include "Game.h"
#include "StringHelpers.hpp"

#include <iostream>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() 
{
	font.loadFromFile("resources/Sansation.ttf");
	statsText.setFont(font);
	statsText.setPosition(5.f, 5.f);
	statsText.setCharacterSize(10);

	gameState = GameState::inMainMenu;
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
		if (event.type == sf::Event::Closed)
			gameWindow.close();

		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
			gameWindow.setView(sf::View(visibleArea));
		}

		if (gameState == GameState::inGame) 
		{
			processInGameEvent(event);
		}

		if (gameState == GameState::inMainMenu)
		{
			int currentMenu = gameMenu.processMenuEvent(event, gameWindow);

			std::cout << currentMenu << std::endl;

			if (currentMenu == 0) { gameState = GameState::inGame; }
			if (currentMenu == 1) { gameState = GameState::inSettingMenu; }
		}
	}
}

void Game::processInGameEvent(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
		handlePlayerInput(event.key.code, true);

	if (event.type == sf::Event::KeyReleased)
		handlePlayerInput(event.key.code, false);
}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f playerMovement(0.f, 0.f);
	float playerSpeed = player.getSpeed();
	if (playerMovingUp)
		playerMovement.y -= playerSpeed;
	if (playerMovingDown)
		playerMovement.y += playerSpeed;
	if (playerMovingLeft)
		playerMovement.x -= playerSpeed;
	if (playerMovingRight)
		playerMovement.x += playerSpeed;

	player.moveEntity(playerMovement * elapsedTime.asSeconds());

	
}

void Game::render() 
{
	gameWindow.clear(sf::Color::Black);

	player.render(gameWindow);

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

	/* Creating the stage */
	//Stage stage{ "Level 1", sf::Vector2f(1000, 1000) };

	/* Creating the player */
	//...//
	
	/* Spawning the Enemies */
	//std::vector<std::unique_ptr<Enemy>> wave = stage.spawn();//

	while (gameWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			elapsedFrame++;

			if (gameState == GameState::inGame && elapsedFrame >= 30)
			{
				auto mousePos = sf::Vector2f(sf::Mouse::getPosition(gameWindow));
				
				mousePos = mousePos - player.getCoords();
				mousePos = mousePos * 100.f / sqrt(mousePos.x*mousePos.x + mousePos.y*mousePos.y);
	
				//Projectile newProjectile = player.shoot(mousePos, true);
				//projectileVector.push_back(newProjectile);
				elapsedFrame = 0;
			}

			processEvent();
			update(TimePerFrame);
		}

		updateStats(elapsedTime);

		if (gameState == GameState::inMainMenu) { gameMenu.renderMainMenu(gameWindow); }
		if (gameState == GameState::inPlayMenu) { gameMenu.renderPlayMenu(gameWindow); }
		if (gameState == GameState::inSettingMenu) { gameMenu.renderSettingMenu(gameWindow); }
		if (gameState == GameState::inGame) { render(); }
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Z)
		playerMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		playerMovingDown = isPressed;
	else if (key == sf::Keyboard::Q)
		playerMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		playerMovingRight = isPressed;
}