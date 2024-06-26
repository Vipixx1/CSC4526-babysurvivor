#include "Game.h"
#include "StringHelpers.hpp"
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
	gameWindow.create(sf::VideoMode(1920, 1080), "Baby Survivor");
	view = gameWindow.getDefaultView();

	font.loadFromFile("resources/Sansation.ttf");
	statsText.setFont(font);
	statsText.setFillColor(sf::Color::White);
	statsText.setPosition(view.getCenter().x - view.getSize().x / 2 + 10.f, view.getCenter().y - view.getSize().y / 2 + 10.f);
	statsText.setCharacterSize(20);

	gameState = GameState::inMenu;
}

std::unique_ptr<Player> Game::loadPlayer(int saveFileNumber)
{
	if (saveFileNumber == 0) { return std::make_unique<Player>( "resources/Entity.json", "player1" ); }
	if (saveFileNumber == 1) { return std::make_unique<Player>( "resources/Entity.json", "player2" ); }
	if (saveFileNumber == 2) { return std::make_unique<Player>( "resources/Entity.json", "player3" ); }

	return std::make_unique<Player>("resources/Entity.json", "player1");
}

void Game::processGeneralEvent(sf::Event event)
{
	/* Handle events that set the gameWindow */
	if (event.type == sf::Event::Closed)
		gameWindow.close();

	if (event.type == sf::Event::Resized)
	{
		sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
		gameWindow.setView(sf::View(visibleArea));
	}
}

void Game::processMenuEvent()
{
	sf::Event event{ sf::Event::Count };

	while (gameWindow.pollEvent(event))
	{
		processGeneralEvent(event);
		// We check the returned value to know if we are launching a game or we are changing the resolution
		int returnValue = gameMenu.processMenuEvent(event, gameWindow);

		// From 0 to 2: load a save file and launch the game
		if (returnValue >= 0 && returnValue < 3)
		{
			// LOAD EVERYTHING NEEDED FOR THE REAL GAME HERE...
			auto player = loadPlayer(returnValue);
			stage.setPlayer(std::move(player));
			stage.startStage();
			gameState = GameState::inGame;
		}

		// From 3 to 8: changeVolume
		if (returnValue >= 3 && returnValue < 9)
		{
			stage.changeVolume(returnValue - 3);
		}

		// 9 means we are going back to the main menu
		if (returnValue == 9)
		{
			gameMenu.renderMainMenu(gameWindow);
		}
	}
}

void Game::processInGameEvent()
{
	sf::Event event{ sf::Event::Count };

	while (gameWindow.pollEvent(event))
	{
		processGeneralEvent(event);
		if (event.type == sf::Event::KeyPressed)
			stage.handleInput(event.key.code, true);

		if (event.type == sf::Event::KeyReleased)
			stage.handleInput(event.key.code, false);
	}
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	gameWindow.setFramerateLimit(60);

	while (gameWindow.isOpen())
	{
		/* Render the menu */
		if (gameState == GameState::inMenu)
		{
			processMenuEvent();

			view.reset(sf::FloatRect(0, 0, 1920, 1080));
			gameWindow.setView(view);


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
			case inUpgradeMenu:
				gameMenu.renderUpgradeMenu(gameWindow);
				break;
			case inGameOverMenu:
				gameMenu.renderGameOverMenu(gameWindow);
				break;
			case inWinMenu:
				gameMenu.renderWinMenu(gameWindow);
				break;
			default:
				break;
			}
		}

		if (gameState == GameState::inGame)
		{
			processInGameEvent();

			/* Updates based on fixed time steps */
			sf::Time elapsedTime = clock.restart();
			timeSinceLastUpdate += elapsedTime;

			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;

				int returnValue = stage.update(TimePerFrame, gameWindow);

				// If the value returned by stage.update is 1 then the player died
				if (returnValue == 1)
				{
					gameState = GameState::inMenu;
					gameMenu.renderGameOverMenu(gameWindow);
				}

				// If the return value is 2 then the player won
				else if (returnValue == 2)
				{
					gameState = GameState::inMenu;
					gameMenu.renderWinMenu(gameWindow);
				}

				view.reset(stage.updateView(gameWindow));
				gameWindow.setView(view);

				updateStatsText(TimePerFrame);
			}

			/* Updates not based on fixed time steps */

			stage.render(gameWindow);
			gameWindow.draw(statsText);

			stage.renderHpBar(gameWindow);
			stage.renderXpBar(gameWindow);
			stage.renderLevelMoney(gameWindow);

			gameWindow.display();
		}
	}
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
