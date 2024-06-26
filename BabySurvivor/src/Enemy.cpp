#include "Enemy.h"
#include "TowardPlayerMovingStrategy.h"
#include "BounceBordersMovingStrategy.h"
#include "OneSimpleShootingStrategy.h"
#include "ThreeSimpleShootingStrategy.h"
#include "FourCrossShootingStrategy.h"
#include <fstream>
#include <random>
#include <cmath>

#include <iostream>

using json = nlohmann::json;



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
		movingStrategy = std::make_unique<TowardPlayerMovingStrategy>();
	}
	else if (movementPattern == "bounceBorders") {
		movingStrategy = std::make_unique<BounceBordersMovingStrategy>();

		static std::mt19937 rng(std::random_device{}());
		static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

		direction = sf::Vector2f(dist(rng), dist(rng));
	}
	
	if (shootingPattern == "oneSimple")
	{
		shootingStrategy = std::make_unique<OneSimpleShootingStrategy>();
	}
	else if (shootingPattern == "threeSimple")
	{
		shootingStrategy = std::make_unique<ThreeSimpleShootingStrategy>();
	}
	else if (shootingPattern == "fourCross" || shootingPattern == "fourCircle")
	{
		shootingStrategy = std::make_unique<FourCrossShootingStrategy>();
	}
}

void Enemy::update(sf::Time elapsedTime, sf::Vector2f stageSize)
{
	if (movingStrategy) {
		sf::Vector2f newDirection = movingStrategy->move(getPosition(), direction, target.getPosition(), getSize(), stageSize);
		direction = newDirection * getSpeed() / sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);

		moveEntity(direction * elapsedTime.asSeconds());
	}
	
	if (shootingStrategy) {
		frameCounter++;
		if (static_cast<float>(frameCounter) >= getShotDelay()) {
			shoot(sf::Vector2f(0, 0));
			frameCounter = 0;
		}
	}

}

void Enemy::shoot(sf::Vector2f projDirection)
{
	projDirection = target.getPosition() - getPosition();
	projDirection = projDirection * getShotSpeed() / sqrt(projDirection.x * projDirection.x + projDirection.y * projDirection.y);

	shootingStrategy->shoot(getProjectiles(), projDirection, getPosition(), getSize(), getDamage());
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

