#include "Stats.h"
#include <fstream>

using json = nlohmann::json;

Stats::Stats(const std::string& filePath) 
{
	std::ifstream f(filePath);
	json data = json::parse(f);

	baseHealth = data.at("baseHealth");
	currentHealt = baseHealth;
	baseDamage = data.at("baseDamage");
	damageMultiplier = data.at("damageMultiplier");
	baseSpeed = data.at("baseSpeed");
}

float Stats::getSpeed() const
{
	return baseSpeed;
}

float Stats::getCurrentHealth() const
{
	return currentHealt;
}

void Stats::setCurrentHealth(float newHealth)
{
	currentHealt = newHealth;
}

float Stats::getDamage() const
{
	return baseDamage * damageMultiplier;
}
