#include "Projectile.h"

Projectile::Projectile(const std::string& filePath, sf::Vector2f coords, sf::Vector2f velocity, float damage, bool isAlly) :
	Entity{ filePath, "projectile", coords},
	velocity{ velocity },
	damage{ damage },
	isAlly{ isAlly } {}

bool Projectile::getTeam() const
{
	return isAlly;
}


sf::Vector2f Projectile::getVelocity() const
{
	return velocity;
}

float Projectile::getDamage() const
{
	return damage;
}

