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
	shotDelay = entityData.at("shotDelay");
	shotSpeed = entityData.at("shotSpeed");
}

float Stats::getSpeed() const
{
	return baseSpeed;
}

float Stats::getCurrentHealth() const
{
	return currentHealth;
}

float Stats::getMaxHealth() const
{
	return baseHealth;
}

void Stats::setMaxHealth(float newMaxHealth)
{
	baseHealth = newMaxHealth;
}

void Stats::setCurrentHealth(float newHealth)
{
	currentHealth = newHealth;
}

float Stats::getDamage() const
{
	return baseDamage * damageMultiplier;
}

void Stats::setDamage(float newDamage)
{
	baseDamage = newDamage;
}

float Stats::getDamageMultiplier() const
{
	return damageMultiplier;
}

void Stats::setDamageMultiplier(float newDamageMultiplier)
{
	damageMultiplier = newDamageMultiplier;
}

float Stats::getShotDelay() const
{
	return shotDelay;
}

float Stats::getShotSpeed() const
{
	return shotSpeed;
}

