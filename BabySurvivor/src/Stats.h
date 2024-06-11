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


public:
	explicit Stats(const std::string& filePath);
	float getSpeed() const;
	float getCurrentHealth() const;
	void setCurrentHealth(float newHealth);
	float getDamage() const;
};