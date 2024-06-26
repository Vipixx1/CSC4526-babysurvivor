#pragma once

#include <SFML/Graphics.hpp>

class MovingStrategy {
public:
	virtual ~MovingStrategy() = default;
	virtual sf::Vector2f move(sf::Vector2f entityPosition, sf::Vector2f targetPosition, sf::Vector2f entitySize, sf::Vector2f stageSize) const = 0;
};
