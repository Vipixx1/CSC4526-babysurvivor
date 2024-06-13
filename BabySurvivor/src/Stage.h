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
	/* test pour afficher les sprites */
	sf::Sprite sprite{};
	sf::Texture texture;

	Stage(std::string_view name, sf::RenderWindow& gameWindow);
	void render(sf::RenderWindow& gameWindow) const;
	std::vector<std::unique_ptr<Enemy>> spawn();

	void setWaveNumber(int newWaveNumber);

	sf::Vector2f getSize() const ;
};