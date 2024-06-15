#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Stats.h"
#include "Projectile.h"
#include "json.hpp"

class LivingEntity : public Entity {
private:
	Stats stats;
	bool dead = false;
	
public:
	LivingEntity(const std::string& filePath, const std::string& livingEntityName, sf::Vector2f coords);

	Projectile shoot(sf::Vector2f velocity, bool isAlly) const;
	void takeDamage(float damageValue);

	float getSpeed() const;
	float getDamage() const;

	bool isDead() const;
	void kill();
};
