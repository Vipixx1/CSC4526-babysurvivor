#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Stats.h"
#include "Projectile.h"
#include "ShootingStrategy.h"
#include "json.hpp"

class LivingEntity : public Entity {
private:
	Stats stats;
	bool isAlly;
	std::unique_ptr<ShootingStrategy> shootingStrategy;

	std::vector<std::unique_ptr<Projectile>> projectiles;

	static std::map<std::string, ShootingStrategy, std::less<>> shootMap;
	
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

	void shoot(sf::Vector2f direction);
};
