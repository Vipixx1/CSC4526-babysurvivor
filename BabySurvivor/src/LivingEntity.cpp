#include "LivingEntity.h"
#include <fstream>

using json = nlohmann::json;

LivingEntity::LivingEntity(const std::string& filePath, sf::Vector2f coords) :
	Entity{ filePath, coords },
	stats{ filePath } {}

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

Projectile LivingEntity::shoot(sf::Vector2f speed, bool isAlly) const
{

	Projectile newProjectile{ getCoords(), speed, stats.getDamage(),isAlly};
	return newProjectile;
}

void LivingEntity::kill()
{
	// TO DO : implement the logic when killing an entity
}