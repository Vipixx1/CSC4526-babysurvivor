#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Stats.h"
#include "Projectile.h"
#include "json.hpp"

class LivingEntity : public Entity {
private:
	Stats stats;
	
public:
	LivingEntity(const std::string& filePath, const std::string& livingEntityName, sf::Vector2f coords);

	Projectile shoot(sf::Vector2f velocity, bool isAlly) const;
	void takeDamage(float damageValue);
	void kill() const;

	float getSpeed() const;
};
