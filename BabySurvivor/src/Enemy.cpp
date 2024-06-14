#include "Enemy.h"
#include <fstream>
#include <random>
#include <cmath>


using json = nlohmann::json;

Enemy::Enemy(const std::string& filePath, const std::string& enemyType, sf::Vector2f coords) :
	LivingEntity{ filePath, enemyType, coords},
	enemyType{ enemyType }
{
	std::ifstream f("resources/Entity.json");

	json allData = json::parse(f);
	json enemyData = allData.at(enemyType);

	movementPattern = enemyData.at("movementPattern");
	shootingPattern = enemyData.at("shootingPattern");

	initializeRandomVelocity();
}

void Enemy::moveAccordingToPattern(sf::Time elapsedTime, sf::Vector2f playerCoords, sf::Vector2f stageSize)
{
	/* Case where enemy is going toward player */
	if (movementPattern == "towardPlayer") 
	{
		currentVelocity = playerCoords - getCoords();

		currentVelocity = currentVelocity * getSpeed() / sqrt(currentVelocity.x * currentVelocity.x + currentVelocity.y * currentVelocity.y);

		moveEntity(currentVelocity * elapsedTime.asSeconds());
	}

	else if (movementPattern == "bounceBorders") {
		sf::Vector2f enemyPosition = getCoords();
		sf::Vector2f enemySize = getSize();

		// Check for collisions with the borders and reverse direction
		if (enemyPosition.x <= 0) {
			enemyPosition.x = 0;
			currentVelocity.x = std::abs(currentVelocity.x);
		}
		else if (enemyPosition.x + enemySize.x >= stageSize.x) {
			enemyPosition.x = stageSize.x - enemySize.x;
			currentVelocity.x = -std::abs(currentVelocity.x);
		}

		if (enemyPosition.y <= 0) {
			enemyPosition.y = 0;
			currentVelocity.y = std::abs(currentVelocity.y);
		}
		else if (enemyPosition.y + enemySize.y >= stageSize.y) {
			enemyPosition.y = stageSize.y - enemySize.y;
			currentVelocity.y = -std::abs(currentVelocity.y);
		}

		// Move the enemy based on its current velocity
		moveEntity(currentVelocity * elapsedTime.asSeconds());
	}
}

void Enemy::initializeRandomVelocity() {
	static std::mt19937 rng(std::random_device{}());
	static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

	currentVelocity.x = dist(rng);
	currentVelocity.y = dist(rng);

	// Normalize the velocity to ensure consistent speed
	float length = std::sqrt(currentVelocity.x * currentVelocity.x + currentVelocity.y * currentVelocity.y);
	currentVelocity = currentVelocity * (getSpeed() / length);
}

