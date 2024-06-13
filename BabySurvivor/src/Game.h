#pragma once 
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Stage.h"
#include "GameMenu.h"

int runGame();

enum class GameState {
	inGame,
	inMainMenu,
	inPlayMenu,
	inSettingMenu,
};

class Game {
private:
	int money{ 0 };
	sf::RenderWindow gameWindow{ sf::VideoMode(1920, 1080), "Baby Survivor"};
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

	Player player{"resources/Entity.json", sf::Vector2f(static_cast<float>(gameWindow.getSize().x)/2, static_cast<float>(gameWindow.getSize().y)/2) };
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


public:
	Game();
	void run();
};
