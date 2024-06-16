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

