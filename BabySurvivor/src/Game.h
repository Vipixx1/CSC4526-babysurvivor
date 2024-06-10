#pragma once 
#include <SFML/Graphics.hpp>

int runGame();

class Game {
private:
	int money;
	sf::RenderWindow gameWindow{ sf::VideoMode(960, 540), "Baby Survivor"};
	sf::Time statsUpdateTime;
	std::size_t numFrames{ 0 };
	sf::Text statsText;
	sf::Font font;
	static const sf::Time	TimePerFrame;

	void processEvent();
	void update(sf::Time elaspedTime);
	void render();

	void updateStats(sf::Time elapsedTime);


public:
	Game();
	void run();
};