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

float LivingEntity::getDamage() const
{
	return stats.getDamage();
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