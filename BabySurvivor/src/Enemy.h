#pragma once
#include "LivingEntity.h"
#include "Collectible.h"
#include "MovingStrategy.h"
#include <string>
#include <memory>

class Enemy : public LivingEntity {
private:
	std::string enemyType;
	sf::Vector2f direction{ 0,0 };

	std::unique_ptr<MovingStrategy> movingStrategy;

	static const float cosTheta;
	static const float sinTheta;

	int frameCounter = 0;
	
	Entity& target;

	void initializeRandomDirection();

	void createProjectile(sf::Vector2f projDirection);

	std::optional<CollectibleType> getRandomCollectible() const;

public:
	Enemy(const std::string& filePath, const std::string& enemyType, Entity& target);
	void update(sf::Time elapsedTime, sf::Vector2f stageSize) override;

	std::optional<std::unique_ptr<Collectible>> dropCollectible() const;
};