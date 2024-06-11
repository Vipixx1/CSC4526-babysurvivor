#include "Stats.h"
#include <fstream>

using json = nlohmann::json;

Stats::Stats(const std::string& filePath) 
{
	std::ifstream f(filePath);
	json data = json::parse(f);

	baseHealth = data["baseHealth"];
	currentHealth = baseHealth;
	baseDamage = data["baseDamage"];
	damageMultiplier = data["damageMultiplier"];
	baseSpeed = data["baseSpeed"];
}

float Stats::getSpeed() const
{
	return baseSpeed;
}

float Stats::getCurrentHealth() const
{
	return currentHealth;
}

void Stats::setCurrentHealth(float newHealth)
{
	currentHealth = newHealth;
}

float Stats::getDamage() const
{
	return baseDamage * damageMultiplier;
}
