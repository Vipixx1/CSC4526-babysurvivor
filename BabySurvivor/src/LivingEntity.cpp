#include "LivingEntity.h"
#include <fstream>

using json = nlohmann::json;

LivingEntity::LivingEntity(const std::string& filePath, const std::string& livingEntityName) :
	Entity{ filePath, livingEntityName },
	stats{ filePath, livingEntityName } {}

std::vector<std::shared_ptr<Projectile>>& LivingEntity::getProjectiles() 
{
	return projectiles;
}

float LivingEntity::getSpeed() const
{
	return stats.getSpeed();
}

<<<<<<< HEAD
float LivingEntity::getCurrentHealth() const
{
	return stats.getCurrentHealth();
}

float LivingEntity::getMaxHealth() const
{
	return stats.getMaxHealth();
}

void LivingEntity::setCurrentHealth(float newHealth)
{
	stats.setCurrentHealth(newHealth);
=======
float LivingEntity::getDamage() const
{
	return stats.getDamage();
>>>>>>> a1cc045a302734ba0d616dd906f76d950ce2d4bd
}

bool LivingEntity::getTeam() const
{
	return isAlly;
}

void LivingEntity::takeDamage(float damageValue) 
{
	float currentHealth = stats.getCurrentHealth();

	if (currentHealth - damageValue < 0)
	{
		setActive(false);
	}
	else
	{
		stats.setCurrentHealth(currentHealth - damageValue);
	}
}