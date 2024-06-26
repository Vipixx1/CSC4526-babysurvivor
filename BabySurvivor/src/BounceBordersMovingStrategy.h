#pragma once
#include "MovingStrategy.h"
#include <SFML/Graphics.hpp>

class BounceBordersMovingStrategy : public MovingStrategy {
public:
	sf::Vector2f move(sf::Vector2f entityPosition, sf::Vector2f entityDirection, sf::Vector2f targetPosition, sf::Vector2f entitySize, sf::Vector2f stageSize) const override;
};