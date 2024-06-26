#pragma once
#include "ShootingStrategy.h"
#include <SFML/Graphics.hpp>

class ThreeSimpleShootingStrategy : public ShootingStrategy {
private:
	static const float cosTheta;
	static const float sinTheta;

public:
	void shoot(std::vector<std::unique_ptr<Projectile>> entityProjectiles, sf::Vector2f projDirection, sf::Vector2f entityPosition, sf::Vector2f entitySize, float entityDamage) override;
};