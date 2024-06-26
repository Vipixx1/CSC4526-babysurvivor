#include "BounceBordersMovingStrategy.h"

sf::Vector2f BounceBordersMovingStrategy::move(sf::Vector2f entityPosition, sf::Vector2f entityDirection, sf::Vector2f targetPosition, sf::Vector2f entitySize, sf::Vector2f stageSize) const
{
	if (entityPosition.x <= 0) {
		entityPosition.x = 0;
		entityDirection.x = std::abs(entityDirection.x);
	}
	else if (entityPosition.x + entitySize.x >= stageSize.x) {
		entityPosition.x = stageSize.x - entityPosition.x;
		entityDirection.x = -std::abs(entityDirection.x);
	}

	if (entityPosition.y <= 0) {
		entityPosition.y = 0;
		entityDirection.y = std::abs(entityDirection.y);
	}
	else if (entityPosition.y + entitySize.y >= stageSize.y) {
		entityPosition.y = stageSize.y - entitySize.y;
		entityDirection.y = -std::abs(entityDirection.y);
	}

	return entityDirection;
}
