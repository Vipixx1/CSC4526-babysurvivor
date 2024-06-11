#pragma once 
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"

int runGame();

class Game {
private:
	int money{ 0 };
	sf::RenderWindow gameWindow{ sf::VideoMode(960, 540), "Baby Survivor"};
	sf::Time statsUpdateTime;
	std::size_t numFrames{ 0 };
	sf::Text statsText;
	sf::Font font;
	static const sf::Time	TimePerFrame;

	Player player;
	bool playerMovingUp{false};
	bool playerMovingDown{false};
	bool playerMovingLeft{false};
	bool playerMovingRight{false};

	void processEvent();
	void update(sf::Time elaspedTime);
	void render();

	void updateStats(sf::Time elapsedTime);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


public:
	Game();
	void run();
};