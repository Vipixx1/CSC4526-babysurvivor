#pragma once 
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Stage.h"
#include "GameMenu.h"
#include "SoundManager.h"

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
	sf::View view;

	sf::Time statsUpdateTime;
	std::size_t numFrames{ 0 };
	sf::Text statsText;
	sf::Font font;
	static const sf::Time TimePerFrame;
	sf::Vector2f cameraPosition{ 0, 0 };

	GameState gameState;
	GameMenu gameMenu;

	SoundManager soundManager;

	int elapsedFrame{ 0 };

	int money{ 0 };
	Stage stage{ "stage_1" };
	Player player{ "resources/Entity.json", "player1", sf::Vector2f(0, 0) };
	bool playerMovingUp{false};
	bool playerMovingDown{false};
	bool playerMovingLeft{false};
	bool playerMovingRight{false};

	std::vector<std::unique_ptr<Projectile>> projectiles;
<<<<<<< HEAD
	std::vector<std::unique_ptr<Collectible>> collectibles;
=======
	std::vector<std::unique_ptr<Enemy>> enemies;
>>>>>>> a1cc045a302734ba0d616dd906f76d950ce2d4bd

	void changeResolution(int newResolutionIndex);

	void loadPlayer(int saveFileNumber, sf::Vector2f stageSize);
	void processEvent();
	void processInGameEvent(sf::Event event);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void renderInGame();

	void updateInGame(sf::Time elapsedTime);
	void updateStatsText(sf::Time elapsedTime);
	void updateCamera();
	void updatePlayer(sf::Time elapsedTime);
	void updateEnemies(sf::Time elapsedTime);
	void handleCollectibleCollection(const Collectible& collectible);
	void updateCollectibles();
	void updateProjectiles(sf::Time elapsedTime);
	void handleAutoFire();

public:
	Game();
	void run();
};
