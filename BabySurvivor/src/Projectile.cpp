#include "Projectile.h"

Projectile::Projectile(sf::Vector2f coords, sf::Vector2f speed, float damage, bool isAlly) :
	Entity{ coords, 1.f, 1.f },
	speed{ speed },
	damage{ damage },
	isAlly{ isAlly } {}


sf::Vector2f Projectile::getSpeed() const
{
	return speed;
}

