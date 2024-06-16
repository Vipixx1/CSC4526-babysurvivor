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

std::optional<CollectibleType> Enemy::getRandomCollectible() const
{
	using enum CollectibleType;

	static std::mt19937 rng(std::random_device{}());
	static std::uniform_int_distribution dist(0, 3);

	int collectible = dist(rng);

	switch (collectible) 
	{
		case 0:
			return experience;
		case 1:
			return health;
		case 2:
			return money;
		case 3:
			return std::nullopt;
		default:
			return std::nullopt;
	}
		
}

std::optional<Collectible> Enemy::dropCollectible() const
{
	using enum CollectibleType;

	std::optional<CollectibleType> collectibleType = getRandomCollectible();

	std::string collectibleName;
	float collectibleValue;

	if (!collectibleType.has_value())
	{
		return std::nullopt;
	}

	else {
		switch (collectibleType.value())
		{
		case experience:
			collectibleName = "experience";
			collectibleValue = 10.f;
			break;

		case health:
			collectibleName = "health";
			collectibleValue = 50.f;
			break;

		case money:
			collectibleName = "money";
			collectibleValue = 1.f;
			break;

		default:
			return std::nullopt;
			break;
		}

		Collectible newCollectible{ "resources/Entity.json" ,collectibleName, getCoords(), collectibleType.value(), collectibleValue};

		return newCollectible;
	}
}

