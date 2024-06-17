#include "Enemy.h"
#include <fstream>
#include <random>
#include <cmath>
#include <iostream>

using json = nlohmann::json;

const float Enemy::cosTheta = 0.92f;
const float Enemy::sinTheta = 0.38f;

Enemy::Enemy(const std::string& filePath, const std::string& enemyType, Entity& target) :
	LivingEntity{ filePath, enemyType, false },
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
	
	frameCounter++;
	if (frameCounter >= 180) {
		shoot(sf::Vector2f(0, 0)); // Shooting pattern can be determined based on enemy type or other criteria
		frameCounter = 0;
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
	if (shootingPattern == "oneSimple")
	{
		projDirection = target.getPosition() - getPosition();
		projDirection = projDirection * 500.f / sqrt(projDirection.x * projDirection.x + projDirection.y * projDirection.y);

		auto newProjectile = std::make_unique<Projectile>("resources/Entity.json", getDamage(), false);
		newProjectile->setPosition(getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2));
		newProjectile->setDirection(projDirection);
		getProjectiles().push_back(std::move(newProjectile));
	}

	else if (shootingPattern == "threeSimple") 
	{
		projDirection = target.getPosition() - getPosition();
		projDirection = projDirection * 500.f / sqrt(projDirection.x * projDirection.x + projDirection.y * projDirection.y);

		auto newProjectile1 = std::make_unique<Projectile>("resources/Entity.json", getDamage(), false);
		newProjectile1->setPosition(getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2));
		newProjectile1->setDirection(projDirection);

		auto newProjectile2 = std::make_unique<Projectile>("resources/Entity.json", getDamage(), false);
		newProjectile2->setPosition(getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2));
		newProjectile2->setDirection(sf::Vector2f(projDirection.x*cosTheta - projDirection.y*sinTheta,
													projDirection.x*sinTheta + projDirection.y*cosTheta));

		auto newProjectile3 = std::make_unique<Projectile>("resources/Entity.json", getDamage(), false);
		newProjectile3->setPosition(getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2));
		newProjectile3->setDirection(sf::Vector2f(projDirection.x * cosTheta + projDirection.y * sinTheta,
									-projDirection.x * sinTheta + projDirection.y * cosTheta));

		getProjectiles().push_back(std::move(newProjectile1));
		getProjectiles().push_back(std::move(newProjectile2));
		getProjectiles().push_back(std::move(newProjectile3));
	}

	else if (shootingPattern == "fourCircle")
	{
		//
	}
	
	else if (shootingPattern == "fourCross")
	{
		projDirection = target.getPosition() - getPosition();
		projDirection = projDirection * 500.f / sqrt(projDirection.x * projDirection.x + projDirection.y * projDirection.y);

		auto newProjectile1 = std::make_unique<Projectile>("resources/Entity.json", getDamage(), false);
		newProjectile1->setPosition(getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2));
		newProjectile1->setDirection(projDirection);

		auto newProjectile2 = std::make_unique<Projectile>("resources/Entity.json", getDamage(), false);
		newProjectile2->setPosition(getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2));
		newProjectile2->setDirection(sf::Vector2f(-projDirection.y, projDirection.x));

		auto newProjectile3 = std::make_unique<Projectile>("resources/Entity.json", getDamage(), false);
		newProjectile3->setPosition(getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2));
		newProjectile3->setDirection(sf::Vector2f(-projDirection.x, -projDirection.y));

		auto newProjectile4 = std::make_unique<Projectile>("resources/Entity.json", getDamage(), false);
		newProjectile3->setPosition(getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2));
		newProjectile3->setDirection(sf::Vector2f(projDirection.y, -projDirection.x));

		getProjectiles().push_back(std::move(newProjectile1));
		getProjectiles().push_back(std::move(newProjectile2));
		getProjectiles().push_back(std::move(newProjectile3));
		getProjectiles().push_back(std::move(newProjectile4));
	}

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

