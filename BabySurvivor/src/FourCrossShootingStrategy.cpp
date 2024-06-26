#include "FourCrossShootingStrategy.h"

void FourCrossShootingStrategy::shoot(std::vector<std::unique_ptr<Projectile>> entityProjectiles, sf::Vector2f projDirection, sf::Vector2f entityPosition, sf::Vector2f entitySize, float entityDamage)
{
	auto projectile1 = createLinearProjectile(projDirection, entityPosition, entitySize, entityDamage);
	auto projectile2 = createLinearProjectile(sf::Vector2f(-projDirection.y, projDirection.x), entityPosition, entitySize, entityDamage);
	auto projectile3 = createLinearProjectile(sf::Vector2f(-projDirection.x, -projDirection.y), entityPosition, entitySize, entityDamage);
	auto projectile4 = createLinearProjectile(sf::Vector2f(projDirection.y, -projDirection.x), entityPosition, entitySize, entityDamage);

	entityProjectiles.push_back(std::move(projectile1));
	entityProjectiles.push_back(std::move(projectile2));
	entityProjectiles.push_back(std::move(projectile3));
	entityProjectiles.push_back(std::move(projectile4));

}
