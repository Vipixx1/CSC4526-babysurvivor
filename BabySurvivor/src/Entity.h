#pragma once
#include <SFML/Graphics.hpp>

class Entity {
private:
	sf::Vector2f coords;

public:
	explicit Entity(sf::Vector2f coords);
	void render();
};