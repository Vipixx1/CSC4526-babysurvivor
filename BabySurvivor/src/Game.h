#pragma once 
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Stage.h"
#include "GameMenu.h"

int startGame();

enum class GameState {
	inGame,
	inMenu,
};

class Game {
private:
	std::vector<std::tuple<int, int>> resolutionVector{ std::make_tuple(1920, 1080),
														std::make_tuple(1280, 800),
														std::make_tuple(1024, 768) };

	int currentResolution{ 0 };

	sf::RenderWindow gameWindow;
	sf::View view = gameWindow.getDefaultView();

	sf::Time statsUpdateTime;
	std::size_t numFrames{ 0 };
	sf::Text statsText;
	sf::Font font;
	static const sf::Time TimePerFrame;
	sf::Vector2f cameraPosition{ 0, 0 };

	GameState gameState;
	GameMenu gameMenu;

	int elapsedFrame{ 0 };

	int money{ 0 };
	Stage stage{ "stage_1" };
	Player player{ "resources/Entity.json", "player1", sf::Vector2f(0, 0) };
	bool playerMovingUp{false};
	bool playerMovingDown{false};
	bool playerMovingLeft{false};
	bool playerMovingRight{false};

	std::vector<std::unique_ptr<Enemy>> enemyVector;
	std::vector<std::unique_ptr<Projectile>> projectileVector;

	void changeResolution(int newResolutionIndex);

	void loadPlayer(int saveFileNumber, sf::Vector2f stageSize);
	void processEvent();
	void processInGameEvent(sf::Event event);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void renderInGame();

	void updateInGame(sf::Time elapsedTime);
	void updateStatsText(sf::Time elapsedTime);
	void updateCamera();
	void updatePlayerMovement(sf::Time elapsedTime);
	void updateEnemiesMovement(sf::Time elapsedTime) const;
	void updateProjectilesMovement(sf::Time elapsedTime) const;
	void handleAutoFire();

public:
	Game();
	void run();
};
