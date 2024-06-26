#include "ThreeSimpleShootingStrategy.h"

const float ThreeSimpleShootingStrategy::cosTheta = 0.92f;
const float ThreeSimpleShootingStrategy::sinTheta = 0.38f;

void ThreeSimpleShootingStrategy::shoot(std::vector<std::unique_ptr<Projectile>>& entityProjectiles, sf::Vector2f projDirection, sf::Vector2f entityPosition, sf::Vector2f entitySize, float entityDamage)
{
	auto projectile1 = createLinearProjectile(projDirection, entityPosition, entitySize, entityDamage);
	auto projectile2 = createLinearProjectile(sf::Vector2f(projDirection.x * cosTheta - projDirection.y * sinTheta, projDirection.x * sinTheta + projDirection.y * cosTheta), 
												entityPosition, entitySize, entityDamage);
	auto projectile3 = createLinearProjectile(sf::Vector2f(projDirection.x * cosTheta + projDirection.y * sinTheta, -projDirection.x * sinTheta + projDirection.y * cosTheta), 
												entityPosition, entitySize, entityDamage);

	entityProjectiles.push_back(std::move(projectile1));
	entityProjectiles.push_back(std::move(projectile2));
	entityProjectiles.push_back(std::move(projectile3));

}
