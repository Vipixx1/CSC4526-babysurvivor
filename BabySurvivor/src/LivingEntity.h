#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Stats.h"
#include "Projectile.h"
#include "json.hpp"

class LivingEntity : public Entity {
private:
	Stats stats;
	bool isAlly = false;
	std::vector<std::shared_ptr<Projectile>> projectiles;
	
public:
	LivingEntity(const std::string& filePath, const std::string& livingEntityName);

	std::vector<std::shared_ptr<Projectile>>& getProjectiles();

	float getSpeed() const;
	float getDamage() const;
	float getMaxHealth() const;
	float getCurrentHealth() const;
	void setCurrentHealth(float newHealth);

	bool getTeam() const;

	bool takeDamage(float damageValue);

	virtual void shoot(sf::Vector2f direction) = 0;
};
