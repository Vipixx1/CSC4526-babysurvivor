#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Stage {
private:
	std::string name;
	sf::Vector2f size;
	int waveNumber = 1;
	bool isWaveBeginning = false;

public:
	Stage(std::string_view name, sf::RenderWindow& gameWindow);
	std::vector<std::unique_ptr<Enemy>> spawn();

	void setWaveNumber(int newWaveNumber);
};