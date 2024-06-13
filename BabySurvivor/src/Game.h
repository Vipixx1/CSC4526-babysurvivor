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
	sf::View view = gameWindow.getDefaultView();
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

	Stage stage{ "level_1", gameWindow };
	Player player{"resources/Entity.json", sf::Vector2f(stage.getSize().x / 2, stage.getSize().y / 2)};
	bool playerMovingUp{false};
	bool playerMovingDown{false};
	bool playerMovingLeft{false};
	bool playerMovingRight{false};
	sf::Vector2f cameraPosition{ static_cast<float>(gameWindow.getSize().x) / 2, static_cast<float>(gameWindow.getSize().y) };


	void processEvent();
	void processInGameEvent(sf::Event event);

	void update(sf::Time elaspedTime);
	void render();

	void updateStatsText(sf::Time elapsedTime);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


public:
	Game();
	void run();
};
