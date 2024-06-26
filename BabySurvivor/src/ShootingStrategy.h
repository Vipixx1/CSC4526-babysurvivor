#pragma once

#include "Projectile.h"

class ShootingStrategy {
public:
	virtual ~ShootingStrategy() = default;
	virtual std::vector<std::unique_ptr<Projectile>> createProjectiles(sf::Vector2f projectileDirection = sf::Vector2f(0,0)) const = 0;
};