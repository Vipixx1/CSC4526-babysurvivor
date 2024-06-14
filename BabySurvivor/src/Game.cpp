#include "Game.h"
#include "StringHelpers.hpp"

#include <fstream>

using json = nlohmann::json;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
{
	resolutionVector.push_back(std::make_tuple(1024, 798));
	resolutionVector.push_back(std::make_tuple(1280, 800));
	resolutionVector.push_back(std::make_tuple(1920, 1080));

	gameWindow.create(sf::VideoMode(std::get<0>(resolutionVector[currentResolution]), std::get<1>(resolutionVector[currentResolution])), "Baby Survivor");

	font.loadFromFile("resources/Sansation.ttf");
	statsText.setFont(font);
	statsText.setFillColor(sf::Color::White);
	statsText.setPosition(view.getCenter().x - view.getSize().x / 2 + 10.f, view.getCenter().y - view.getSize().y / 2 + 10.f);
	statsText.setCharacterSize(20);

	gameState = GameState::inMenu;
}

void Game::loadPlayer(int saveFileNumber)
{
	if (saveFileNumber == 0) {player = Player{ "resources/Entity.json", "player1", sf::Vector2f(480, 270) };}
	if (saveFileNumber == 1) { player = Player{ "resources/Entity.json", "player2", sf::Vector2f(480, 270) }; }
	if (saveFileNumber == 2) { player = Player{ "resources/Entity.json", "player3", sf::Vector2f(480, 270) }; }
}

void Game::changeResolution(int newResolutionIndex)
{
	gameWindow.create(sf::VideoMode(std::get<0>(resolutionVector[newResolutionIndex]), std::get<1>(resolutionVector[newResolutionIndex])), "Baby Survivor");
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

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
			gameWindow.create(sf::VideoMode(1920, 1080), "Baby Survivor", sf::Style::Fullscreen);

		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
			gameWindow.setView(sf::View(visibleArea));
		}

		if (gameState == GameState::inGame) 
		{
			processInGameEvent(event);
		}

		if (gameState == GameState::inMenu)
		{
			int returnValue = gameMenu.processMenuEvent(event, gameWindow);

			// We check the returned value to know if we are lauching a game or we are changing the resolution
			// From 0 to 2 is changing the resolution
			// From 3 to 5 is loading a save file and lauching a game

			if (returnValue >= 0 && returnValue < 3)
			{
				loadPlayer(returnValue);
				gameState = GameState::inGame;
			}

			if (returnValue >= 3 && returnValue < 6)
			{
				changeResolution(returnValue - 3);
			}

			if (returnValue == 6)
			{
				gameMenu.renderMainMenu(gameWindow);
			}
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
	/* Update player's movement */
	sf::Vector2f playerVelocity(0.f, 0.f);
	float playerSpeed = player.getSpeed();
	if (playerMovingUp)
		playerVelocity.y -= playerSpeed;
	if (playerMovingDown)
		playerVelocity.y += playerSpeed;
	if (playerMovingLeft)
		playerVelocity.x -= playerSpeed;
	if (playerMovingRight)
		playerVelocity.x += playerSpeed;

	player.moveEntity(playerVelocity * elapsedTime.asSeconds());

	/* Update the movement of enemies */
	for (auto const& enemy : currentWave)
	{
		float enemySpeed = enemy->getSpeed();
		auto enemyVelocity = player.getCoords() - enemy->getCoords();

		enemyVelocity = enemyVelocity * enemySpeed / sqrt(enemyVelocity.x * enemyVelocity.x + enemyVelocity.y * enemyVelocity.y);

		enemy->moveEntity(enemyVelocity * elapsedTime.asSeconds());

	}

	/* Update the movement of projectiles */
	for (auto& projectile : projectileVector)
	{
		projectile.moveEntity(projectile.getVelocity() * elapsedTime.asSeconds());

		//[TODO] check if the bullet hit an ennemy or get out of the screen and do the appropriate action
	}
}

void Game::render() 
{
	gameWindow.clear(sf::Color::Black);

	stage.render(gameWindow);

	player.render(gameWindow);

	for (const auto& enemy : currentWave)
	{
		enemy->render(gameWindow);
	}

	for (const auto& projectile : projectileVector)
	{
		projectile.render(gameWindow);
	}

	gameWindow.draw(statsText);
	gameWindow.display();
}

void Game::updateStatsText(sf::Time elapsedTime)
{
	statsText.setPosition(view.getCenter().x - view.getSize().x/2 + 10.f, view.getCenter().y - view.getSize().y/2 + 10.f);
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
	
	/* Spawning the Enemies */
	currentWave = stage.spawn();

	while (gameWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			elapsedFrame++;

			if (elapsedFrame >= 30)
			{
				/* The player auto fire once every 30 frames */

				// Get the mouse position in the window
				sf::Vector2i pixelPos = sf::Mouse::getPosition(gameWindow);
				// Convert it to world coordinates
				sf::Vector2f worldPos = gameWindow.mapPixelToCoords(pixelPos);

				worldPos = worldPos - player.getCoords();
				worldPos = worldPos * 500.f / sqrt(worldPos.x * worldPos.x + worldPos.y * worldPos.y);

				Projectile newProjectile = player.shoot(worldPos, true);
				projectileVector.push_back(newProjectile);

				elapsedFrame = 0;
			}

			processEvent();
			update(TimePerFrame);
		}

		/* Make the camera follow the player */
		cameraPosition.x = player.getCoords().x + (player.getSize().x / 2) - (static_cast<float>(gameWindow.getSize().x) / 2);
		cameraPosition.y = player.getCoords().y + (player.getSize().y / 2) - (static_cast<float>(gameWindow.getSize().y) / 2);

		/* Check if the camera is within the stage borders*/
		if (cameraPosition.x < 0) cameraPosition.x = 0;
		if (cameraPosition.x + static_cast<float>(gameWindow.getSize().x) > stage.getSize().x) cameraPosition.x = stage.getSize().x - static_cast<float>(gameWindow.getSize().x);
		if (cameraPosition.y < 0) cameraPosition.y = 0;
		if (cameraPosition.y + static_cast<float>(gameWindow.getSize().y) > stage.getSize().y) cameraPosition.y = stage.getSize().y - static_cast<float>(gameWindow.getSize().y);

		view.reset(sf::FloatRect(cameraPosition.x, cameraPosition.y, static_cast<float>(gameWindow.getSize().x), static_cast<float>(gameWindow.getSize().y)));

		gameWindow.setView(view);

		updateStatsText(elapsedTime);

		if (gameState == GameState::inMenu)
		{
			if (gameMenu.getMenuState() == MenuState::inMainMenu) { gameMenu.renderMainMenu(gameWindow); }
			if (gameMenu.getMenuState() == MenuState::inPlayMenu) { gameMenu.renderPlayMenu(gameWindow); }
			if (gameMenu.getMenuState() == MenuState::inSettingsMenu) { gameMenu.renderSettingMenu(gameWindow); }
		}

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
