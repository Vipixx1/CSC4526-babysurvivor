#include "BounceBordersMovingStrategy.h"
#include <random>

sf::Vector2f BounceBordersMovingStrategy::move(sf::Vector2f entityPosition, sf::Vector2f targetPosition, sf::Vector2f entitySize, sf::Vector2f stageSize) const
{
	static std::mt19937 rng(std::random_device{}());
	static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

	sf::Vector2f direction{ dist(rng), dist(rng) };

	if (entityPosition.x <= 0) {
		entityPosition.x = 0;
		direction.x = std::abs(direction.x);
	}
	else if (entityPosition.x + entitySize.x >= stageSize.x) {
		entityPosition.x = stageSize.x - entityPosition.x;
		direction.x = -std::abs(direction.x);
	}

	if (entityPosition.y <= 0) {
		entityPosition.y = 0;
		direction.y = std::abs(direction.y);
	}
	else if (entityPosition.y + entitySize.y >= stageSize.y) {
		entityPosition.y = stageSize.y - entitySize.y;
		direction.y = -std::abs(direction.y);
	}

	return direction;
}
