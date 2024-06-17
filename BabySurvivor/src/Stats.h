#pragma once

#include <string>
#include <json.hpp>

class Stats {
private:
	float baseHealth{ 0 };
	float currentHealth{ 0 };
	float baseDamage{ 0 };
	float damageMultiplier{ 0 };
	float baseSpeed{ 0 };
	int shotDelay{ 0 };
	float shotSpeed{ 0 };

public:
	explicit Stats(const std::string& filePath, const std::string& livingEntityName);

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

	

	
};