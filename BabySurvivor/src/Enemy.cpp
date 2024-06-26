#include "Enemy.h"
#include "TowardPlayerMovingStrategy.h"
#include "BounceBordersMovingStrategy.h"
#include <fstream>
#include <random>
#include <cmath>

#include <iostream>

using json = nlohmann::json;

const float Enemy::cosTheta = 0.92f;
const float Enemy::sinTheta = 0.38f;

Enemy::Enemy(const std::string& filePath, const std::string& enemyType, Entity& target) :
	LivingEntity{ filePath, enemyType, false},
	enemyType{ enemyType },
	target{ target }
{
	std::ifstream f("resources/Entity.json");

	json allData = json::parse(f);
	json enemyData = allData.at(enemyType);

	std::string movementPattern = enemyData.at("movementPattern");
	std::string shootingPattern = enemyData.at("shootingPattern");

	if (movementPattern == "towardPlayer") {
		std::cout << "tp" << std::endl;
		movingStrategy = std::make_unique<TowardPlayerMovingStrategy>();
	}
	if (movementPattern == "bounceBorders") {
		std::cout << "b" << std::endl;
		movingStrategy = std::make_unique<BounceBordersMovingStrategy>();

		static std::mt19937 rng(std::random_device{}());
		static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

		direction = sf::Vector2f(dist(rng), dist(rng));
	}
	else {
		movingStrategy = std::make_unique<TowardPlayerMovingStrategy>();
	}

	initializeRandomDirection();
}

void Enemy::update(sf::Time elapsedTime, sf::Vector2f stageSize)
{
	sf::Vector2f newDirection = movingStrategy->move(getPosition(), direction, target.getPosition(), getSize(), stageSize);
	direction = newDirection * getSpeed() / sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);

	moveEntity(direction * elapsedTime.asSeconds());
	checkBounds(stageSize);
	
	frameCounter++;
	if (static_cast<float>(frameCounter) >= getShotDelay()) {
		shoot(sf::Vector2f(0, 0));
		frameCounter = 0;
	}
}

void Enemy::createProjectile(sf::Vector2f projDirection) 
{
	auto projPosition = getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2);

	auto projectile = std::make_unique<Projectile>("resources/Entity.json", "projectileEnemy", getDamage(), false);
	projectile->setPosition(projPosition);
	projectile->setDirection(projDirection);
	getProjectiles().push_back(std::move(projectile));
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

std::optional<std::unique_ptr<Collectible>> Enemy::dropCollectible() const
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
			collectibleValue = 5.f;
			break;

		case health:
			collectibleName = "health";
			collectibleValue = 20.f;
			break;

		case money:
			collectibleName = "money";
			collectibleValue = 5.f;
			break;

		default:
			return std::nullopt;
			break;
		}

		auto newCollectible = std::make_unique<Collectible>( "resources/Entity.json" , collectibleName, collectibleType.value(), collectibleValue);
		newCollectible->setPosition(getPosition());

		return std::move(newCollectible);
	}
}

