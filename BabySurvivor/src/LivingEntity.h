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
	void setDamage(float newDamage);

	float getDamageMultiplier() const;
	void setDamageMultiplier(float newDamageMultiplier);

	float getCurrentHealth() const;
	void setCurrentHealth(float newHealth);

	float getMaxHealth() const;
	void setMaxHealth(float newMaxHealt);

	bool isDead() const;
	void kill();
};
