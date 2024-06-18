#pragma once
#include "LivingEntity.h"
#include "Collectible.h"
#include <string>

class Enemy : public LivingEntity {
private:
	std::string enemyType;
	std::string movementPattern;
	std::string shootingPattern;
	float shootDelay = 0;
	sf::Vector2f direction{ 0,0 };

	static const float cosTheta;
	static const float sinTheta;

	int frameCounter = 0;
	
	Entity& target;

	void initializeRandomDirection();

	void createProjectile(sf::Vector2f projDirection);

	std::optional<CollectibleType> getRandomCollectible() const;

public:
	Enemy(const std::string& filePath, const std::string& enemyType, Entity& target);
	void update(sf::Time elapsedTime) override;
	void checkBounds(sf::Vector2f stageSize) override;

	void shoot(sf::Vector2f projDirection) override;

	std::optional<Collectible> dropCollectible() const;
};



