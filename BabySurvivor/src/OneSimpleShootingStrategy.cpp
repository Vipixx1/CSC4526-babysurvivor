#include "OneSimpleShootingStrategy.h"

void OneSimpleShootingStrategy::shoot(std::vector<std::unique_ptr<Projectile>> entityProjectiles, sf::Vector2f projDirection, sf::Vector2f entityPosition, sf::Vector2f entitySize, float entityDamage)
{
	auto projectile = createLinearProjectile(projDirection, entityPosition, entitySize, entityDamage);

	entityProjectiles.push_back(std::move(projectile));

}
