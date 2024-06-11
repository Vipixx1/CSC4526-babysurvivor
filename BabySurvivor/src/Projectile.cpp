#include "Projectile.h"

Projectile::Projectile(sf::Vector2f coords, int damage, bool isAlly) :
	coords{ coords },
	damage{ damage },
	isAlly{ isAlly } {}
