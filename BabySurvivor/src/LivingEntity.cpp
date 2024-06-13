#include "LivingEntity.h"
#include <fstream>

using json = nlohmann::json;

LivingEntity::LivingEntity(const std::string& filePath, const std::string& livingEntityName, sf::Vector2f coords) :
	Entity{ filePath, livingEntityName, coords },
	stats{ filePath, livingEntityName } {}

float LivingEntity::getSpeed() const
{
	return stats.getSpeed();
}

void LivingEntity::takeDamage(float damageValue) 
{
	float currentHealth = stats.getCurrentHealth();

	if (currentHealth - damageValue < 0)
	{
		kill();
	}
	else
	{
		stats.setCurrentHealth(currentHealth - damageValue);
	}
}

Projectile LivingEntity::shoot(sf::Vector2f velocity, bool isAlly) const
{

	Projectile newProjectile{ "resources/Entity.json", getCoords(), velocity, stats.getDamage(), isAlly};
	return newProjectile;
}

void LivingEntity::kill() const
{
	// TO DO : implement the logic when killing an entity
}
