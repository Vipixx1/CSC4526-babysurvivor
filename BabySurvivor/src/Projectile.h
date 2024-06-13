#pragma once

#include "Entity.h"

class Projectile : public Entity {
private:
	sf::Vector2f velocity;
	float damage;
	bool isAlly;

public:
	explicit Projectile(const std::string& filePath, sf::Vector2f coords, sf::Vector2f velocity, float damage, bool isAlly);
	sf::Vector2f getVelocity() const;
};