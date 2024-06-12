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
	LivingEntity(const std::string& filePath, sf::Vector2f coords);

	Projectile shoot(sf::Vector2f speed, bool isAlly) const;
	void takeDamage(float damageValue);
	void kill();

	float getSpeed() const;
};