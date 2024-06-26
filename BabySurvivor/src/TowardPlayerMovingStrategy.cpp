#include "TowardPlayerMovingStrategy.h"


sf::Vector2f TowardPlayerMovingStrategy::move(sf::Vector2f entityPosition, sf::Vector2f entityDirection, sf::Vector2f targetPosition, sf::Vector2f entitySize, sf::Vector2f stageSize) const
{
	return targetPosition - entityPosition;
}
