#include "Stats.h"
#include <fstream>

using json = nlohmann::json;

Stats::Stats(const std::string& filePath, const std::string& livingEntityName)
{
	std::ifstream f(filePath);
	json allData = json::parse(f);
	json entityData = allData.at(livingEntityName);

	baseHealth = entityData.at("baseHealth");
	currentHealth = baseHealth;
	baseDamage = entityData.at("baseDamage");
	damageMultiplier = entityData.at("damageMultiplier");
	baseSpeed = entityData.at("baseSpeed");
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
