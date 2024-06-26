#pragma once
#include "Projectile.h"

class ShootingStrategy {
protected:
	std::unique_ptr<Projectile> createLinearProjectile(sf::Vector2f projDirection, sf::Vector2f entityPosition, sf::Vector2f entitySize, float entityDamage) {
		auto projPosition = entityPosition + sf::Vector2f(entitySize.x / 2, entitySize.y / 2);

		auto projectile = std::make_unique<Projectile>("resources/Entity.json", "projectileEnemy", entityDamage, false);
		projectile->setPosition(projPosition);
		projectile->setDirection(projDirection);
		return std::move(projectile);
	}

public:
	virtual ~ShootingStrategy() = default;
	virtual void shoot(std::vector<std::unique_ptr<Projectile>> entityProjectiles, sf::Vector2f projDirection, sf::Vector2f entityPosition, sf::Vector2f entitySize, float entityDamage) = 0;
};