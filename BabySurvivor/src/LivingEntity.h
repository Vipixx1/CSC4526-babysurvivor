#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Stats.h"
#include "Projectile.h"
#include "json.hpp"

class LivingEntity : public Entity {
private:
	Stats stats;
	bool isAlly;

	std::vector<std::unique_ptr<Projectile>> projectiles;
	
public:
	LivingEntity(const std::string& filePath, const std::string& livingEntityName, bool isAlly);

	std::vector<std::unique_ptr<Projectile>>& getProjectiles();

	float getMaxHealth() const;
	void setMaxHealth(float newMaxHealth);
	float getCurrentHealth() const;
	void setCurrentHealth(float newHealth);

	float getDamage() const;
	void setDamage(float newDamage);
	float getDamageMultiplier() const;
	void setDamageMultiplier(float newDamageMultiplier);

	float getSpeed() const;

	float getShotDelay() const;
	float getShotSpeed() const;

	bool getTeam() const;

	virtual bool takeDamage(float damageValue);

	virtual void shoot(sf::Vector2f direction) = 0;
};
