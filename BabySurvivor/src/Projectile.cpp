#include "Projectile.h"

Projectile::Projectile(const std::string& filePath, sf::Vector2f coords, sf::Vector2f speed, float damage, bool isAlly) :
	Entity{ filePath, "projectile", coords},
	speed{ speed },
	damage{ damage },
	isAlly{ isAlly } {}


sf::Vector2f Projectile::getSpeed() const
{
	return speed;
}

