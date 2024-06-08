#pragma once

#include <SFML/Graphics.hpp>

int runGame();

class Game {
private:
	int money;
	sf::RenderWindow gameWindow;

public:
	Game();
	void display();
};