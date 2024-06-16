#include "Game.h"
#include "StringHelpers.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

int startGame() {
	Game game;
	game.run();
	return 1;
}

Game::Game()
{
	gameWindow.create(sf::VideoMode(std::get<0>(resolutionVector[currentResolution]), std::get<1>(resolutionVector[currentResolution])), "Baby Survivor");
	view = gameWindow.getDefaultView();

	font.loadFromFile("resources/Sansation.ttf");
	statsText.setFont(font);
	statsText.setFillColor(sf::Color::White);
	statsText.setPosition(view.getCenter().x - view.getSize().x / 2 + 10.f, view.getCenter().y - view.getSize().y / 2 + 10.f);
	statsText.setCharacterSize(20);

	gameState = GameState::inMenu;
}

void Game::loadPlayer(int saveFileNumber, sf::Vector2f stageSize)
{
	if (saveFileNumber == 0) { player = Player{ "resources/Entity.json", "player1", sf::Vector2f(stageSize.x / 2, stageSize.y / 2) }; }
	if (saveFileNumber == 1) { player = Player{ "resources/Entity.json", "player2", sf::Vector2f(stageSize.x / 2, stageSize.y / 2) }; }
	if (saveFileNumber == 2) { player = Player{ "resources/Entity.json", "player3", sf::Vector2f(stageSize.x / 2, stageSize.y / 2) }; }
}

void Game::changeResolution(int newResolutionIndex)
{
	gameWindow.create(sf::VideoMode(std::get<0>(resolutionVector[newResolutionIndex]), std::get<1>(resolutionVector[newResolutionIndex])), "Baby Survivor");
	gameWindow.setFramerateLimit(60);
}

void Game::processEvent() 
{
	sf::Event event{ sf::Event::Count };

	while (gameWindow.pollEvent(event))
	{
		/* Handle events that set the gameWindow */
		if (event.type == sf::Event::Closed)
			gameWindow.close();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
			gameWindow.create(sf::VideoMode(1920, 1080), "Baby Survivor", sf::Style::Fullscreen);

		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
			gameWindow.setView(sf::View(visibleArea));
		}

		/* Handle events related to the gameMenu */
		if (gameState == GameState::inMenu)
		{
			// We check the returned value to know if we are launching a game or we are changing the resolution
			int returnValue = gameMenu.processMenuEvent(event, gameWindow);
			
			// From 0 to 2: changing the resolution
			if (returnValue >= 0 && returnValue < 3)
			{
				// LOAD THE GAME HERE...
				// stage = Stage{ "stage_2" }; Change if multiple stages exist BUT IT'S CURRENTLY BUGGUED !!
				loadPlayer(returnValue, stage.getSize());

				gameState = GameState::inGame;
			}

			// From 3 to 5: loading a save file and launching a game
			if (returnValue >= 3 && returnValue < 6)
			{
				changeResolution(returnValue - 3);
			}

			// 6 means we are going back to the main menu
			if (returnValue == 6)
			{
				gameMenu.renderMainMenu(gameWindow);
			}

			// From 7 to 12 : changing the volume setting
			if (returnValue >= 7 && returnValue < 13)
			{
				soundManager.changeVolume(returnValue - 7);
			}
		}

		/* Handle events related to the true game */
		if (gameState == GameState::inGame)
		{
			processInGameEvent(event);
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

	// debug:
	if (key == sf::Keyboard::A)
		std::cout << "Pressed A:" << std::endl;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	gameWindow.setFramerateLimit(60);

	while (gameWindow.isOpen())
	{
		processEvent();

		if (gameState == GameState::inMenu)
		{
			switch (gameMenu.getMenuState())
			{
				using enum MenuState;
				case inMainMenu:
					gameMenu.renderMainMenu(gameWindow);
					break;
				case inPlayMenu:
					gameMenu.renderPlayMenu(gameWindow);
					break;
				case inSettingsMenu:
					gameMenu.renderSettingMenu(gameWindow);
					break;
			}
		}

		if (gameState == GameState::inGame)
		{
			/* Spawning the Enemies */
			if (stage.getSpawningBool()) {
				enemies = stage.spawn();
				stage.setSpawningBool(false);
			}

			/* Make the game update fixed based on time steps */
			sf::Time elapsedTime = clock.restart();
			timeSinceLastUpdate += elapsedTime;
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;

				elapsedFrame++;
				if (elapsedFrame >= 30)
				{
					handleAutoFire();
					elapsedFrame = 0;
				}
				updateInGame(TimePerFrame);
			}
			updateCamera();
			updateStatsText(elapsedTime);
			renderInGame();
		}
	}
}

void Game::renderInGame()
{
	gameWindow.clear(sf::Color::Black);

	stage.render(gameWindow);

	player.render(gameWindow);

	for (const auto& enemy : enemies)
	{
		enemy->render(gameWindow);
	}

	for (const auto& projectile : projectiles)
	{
		projectile->render(gameWindow);
	}

	gameWindow.draw(statsText);
	gameWindow.display();
}

void Game::updateInGame(sf::Time elapsedTime)
{
	/* Update player's movement */
	updatePlayer(elapsedTime);

	/* Update the movement of enemies */
	updateEnemies(elapsedTime);

	/* Update the projectiles */
	updateProjectiles(elapsedTime);
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

void Game::updateCamera() 
{
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
}

void Game::updatePlayer(sf::Time elapsedTime) {
	sf::Vector2f playerVelocity(0.f, 0.f);
	float playerSpeed = player.getSpeed();
	sf::Vector2f playerPosition = player.getCoords();
	sf::Vector2f playerSize = player.getSize();
	sf::Vector2f stageSize = stage.getSize();

	if (playerMovingUp)
		playerVelocity.y -= playerSpeed;
	if (playerMovingDown)
		playerVelocity.y += playerSpeed;
	if (playerMovingLeft)
		playerVelocity.x -= playerSpeed;
	if (playerMovingRight)
		playerVelocity.x += playerSpeed;

	// Calculate the potential new position
	sf::Vector2f newPosition = playerPosition + playerVelocity * elapsedTime.asSeconds();

	// Boundary checks
	if (newPosition.x < 0) newPosition.x = 0;
	if (newPosition.y < 0) newPosition.y = 0;
	if (newPosition.x + playerSize.x > stageSize.x) newPosition.x = stageSize.x - playerSize.x;
	if (newPosition.y + playerSize.y > stageSize.y) newPosition.y = stageSize.y - playerSize.y;

	// Set the player's new position
	player.setCoords(newPosition);


	/* Check for collision with enemies */
	for (auto const& enemy : enemies) {
		if (player.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
			player.takeDamage(enemy->getDamage());
			//Add invulnerability frames...
			break;
		}
	}
}

void Game::updateEnemies(sf::Time elapsedTime) {
	for (auto it = enemies.begin(); it != enemies.end();) 
	{
		auto const& enemy = *it;

		/* Move enemy based on its pattern */ 
		enemy->moveAccordingToPattern(elapsedTime, player.getCoords(), stage.getSize());

		/* Check if the enemy is dead */
		if (enemy->isDead()) 
		{
			it = enemies.erase(it);
		}
		else ++it;
	}
	
}

void Game::updateProjectiles(sf::Time elapsedTime) {
	for (auto it = projectiles.begin(); it != projectiles.end();) {
		auto const& projectile = *it;

		/* Update the projectile's movement */
		projectile->moveEntity(projectile->getVelocity() * elapsedTime.asSeconds());

		/* Check for collision with opposite team */
		bool collided = false;

		if (projectile->getTeam()) {	// player's projectiles
			for (auto const& enemy : enemies) {
				if (projectile->getGlobalBounds().intersects(enemy->getGlobalBounds())) {
					collided = true;
					enemy->takeDamage(projectile->getDamage());
					break;
				}
			}
		} else {						//Enemies's projectiles
			if (projectile->getGlobalBounds().intersects(player.getGlobalBounds())) {
				collided = true;
				player.takeDamage(projectile->getDamage());
				break;
			}
		}
		

		/* Check if the projectile is Out Of Bounds (OOB) */
		if (auto pos = projectile->getCoords();
			pos.x < 0 
			|| pos.x > stage.getSize().x 
			|| pos.y < 0 
			|| pos.y > stage.getSize().y) 
		{
			collided = true;
		}

		/* Remove the projectile if it collided or OOB */
		if (collided) {
			it = projectiles.erase(it);
		}
		else {
			++it;
		}
	}
	
}

void Game::handleAutoFire()
{
	// Get the mouse position in the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(gameWindow);
	// Convert it to world coordinates
	sf::Vector2f worldPos = gameWindow.mapPixelToCoords(pixelPos);

	// Calculate direction and normalize
	worldPos = worldPos - player.getCoords();
	worldPos = worldPos * 500.f / sqrt(worldPos.x * worldPos.x + worldPos.y * worldPos.y);

	// Create and shoot a new projectile
	auto newProjectile = std::make_unique<Projectile>(player.shoot(worldPos, true));
	projectiles.push_back(std::move(newProjectile));
	soundManager.playSound("resources/audio/playerShoot.wav");
}
