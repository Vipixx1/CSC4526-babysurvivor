#pragma once
#include "LivingEntity.h"
#include "Collectible.h"
#include "MovingStrategy.h"
#include "ShootingStrategy.h"
#include <string>
#include <memory>

class Enemy : public LivingEntity {
private:
	std::string enemyType;
	sf::Vector2f direction{ 0,0 };

	std::unique_ptr<MovingStrategy> movingStrategy;
	std::unique_ptr<ShootingStrategy> shootingStrategy;

	int frameCounter = 0;
	
	Entity& target;

	std::optional<CollectibleType> getRandomCollectible() const;

public:
	Enemy(const std::string& filePath, const std::string& enemyType, Entity& target);
	void update(sf::Time elapsedTime, sf::Vector2f stageSize) override;

	void shoot(sf::Vector2f projDirection) override;

	std::optional<std::unique_ptr<Collectible>> dropCollectible() const;
};