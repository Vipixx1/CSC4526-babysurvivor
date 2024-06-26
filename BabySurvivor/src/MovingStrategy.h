#pragma once

#include <SFML/Graphics.hpp>

class MovingStrategy {
public:
	virtual ~MovingStrategy() = default;
	virtual sf::Vector2f move(sf::Vector2f entityPosition, sf::Vector2f playerPosition = sf::Vector2f(0,0)) const = 0;
};