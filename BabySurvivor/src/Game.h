#pragma once 
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Stage.h"
#include "GameMenu.h"

int runGame();

enum class GameState {
	inGame,
	inMenu,
};

class Game {
private:

	std::vector<std::tuple<int, int>> resolutionVector;

	int currentResolution{ 0 };

	int money{ 0 };
	sf::RenderWindow gameWindow;
	sf::Time statsUpdateTime;
	std::size_t numFrames{ 0 };
	sf::Text statsText;
	sf::Font font;
	static const sf::Time	TimePerFrame;

	std::vector <std::unique_ptr<Enemy>> currentWave;
	std::vector<Projectile> projectileVector;

	GameState gameState;

	GameMenu gameMenu;

	int elapsedFrame{ 0 };

	Player player{"resources/Entity.json", "player1", sf::Vector2f(480, 270) };
	bool playerMovingUp{false};
	bool playerMovingDown{false};
	bool playerMovingLeft{false};
	bool playerMovingRight{false};

	void processEvent();
	void processInGameEvent(sf::Event event);

	void update(sf::Time elaspedTime);
	void render();

	void updateStats(sf::Time elapsedTime);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void loadPlayer(int saveFileNumber);
	void changeResolution(int newResolutionIndex);

public:
	Game();
	void run();
};
