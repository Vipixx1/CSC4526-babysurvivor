#include "Enemy.h"
#include <fstream>
#include <random>
#include <cmath>


using json = nlohmann::json;

Enemy::Enemy(const std::string& filePath, const std::string& enemyType, Entity& target) :
	LivingEntity{ filePath, enemyType},
	enemyType{ enemyType },
	target{ target }
{
	std::ifstream f("resources/Entity.json");

	json allData = json::parse(f);
	json enemyData = allData.at(enemyType);

	movementPattern = enemyData.at("movementPattern");
	shootingPattern = enemyData.at("shootingPattern");

	initializeRandomDirection();

}

void Enemy::update(sf::Time elapsedTime)
{
	if (movementPattern == "towardPlayer") 
	{
		direction = target.getPosition() - getPosition();
		direction = direction * getSpeed() / sqrt(direction.x * direction.x + direction.y * direction.y);

		moveEntity(direction * elapsedTime.asSeconds());
	}

	else if (movementPattern == "bounceBorders") {
		moveEntity(direction * elapsedTime.asSeconds());
	}
}

void Enemy::checkBounds(sf::Vector2f stageSize)
{
	if (movementPattern == "bounceBorders") {
		sf::Vector2f enemyPosition = getPosition();
		sf::Vector2f enemySize = getSize();

		if (enemyPosition.x <= 0) {
			enemyPosition.x = 0;
			direction.x = std::abs(direction.x);
		}
		else if (enemyPosition.x + enemySize.x >= stageSize.x) {
			enemyPosition.x = stageSize.x - enemySize.x;
			direction.x = -std::abs(direction.x);
		}

		if (enemyPosition.y <= 0) {
			enemyPosition.y = 0;
			direction.y = std::abs(direction.y);
		}
		else if (enemyPosition.y + enemySize.y >= stageSize.y) {
			enemyPosition.y = stageSize.y - enemySize.y;
			direction.y = -std::abs(direction.y);
		}
	}

	else { Entity::checkBounds(stageSize); }
}


void Enemy::shoot(sf::Vector2f projDirection)
{
	auto newProjectile = std::make_unique<Projectile>("resources/Entity.json", getDamage(), false);
	newProjectile->setPosition(getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2));
	newProjectile->setDirection(projDirection);
	getProjectiles().push_back(std::move(newProjectile));
}

void Enemy::initializeRandomDirection() {
	static std::mt19937 rng(std::random_device{}());
	static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

	direction.x = dist(rng);
	direction.y = dist(rng);

	// Normalize the velocity to ensure consistent speed
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction = direction * (getSpeed() / length);
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

		Collectible newCollectible{ "resources/Entity.json" , collectibleName, collectibleType.value(), collectibleValue};
		newCollectible.setPosition(getPosition());

		return newCollectible;
	}
}

