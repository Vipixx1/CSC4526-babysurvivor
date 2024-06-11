#pragma once

#include "Entity.h"

class Projectile : public Entity {
private:
	sf::Vector2f speed;
	float damage;
	bool isAlly;

public:
	explicit Projectile(sf::Vector2f coords, sf::Vector2f speed, float damage, bool isAlly);
	sf::Vector2f getSpeed() const;
};