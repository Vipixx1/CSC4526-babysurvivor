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

void LivingEntity::setDamage(float newDamage)
{
	stats.setDamage(newDamage);
}

float LivingEntity::getCurrentHealth() const
{
	return stats.getCurrentHealth();
}

void LivingEntity::setCurrentHealth(float newHealth)
{
	stats.setCurrentHealth(newHealth);
}

float LivingEntity::getMaxHealth() const
{
	return stats.getMaxHealth();
}

void LivingEntity::setMaxHealth(float newMaxHealt)
{
	stats.setMaxHealth(newMaxHealt);
}

float LivingEntity::getDamageMultiplier() const
{
	return stats.getDamageMultiplier();
}

void LivingEntity::setDamageMultiplier(float newDamageMultiplier)
{
	stats.setDamageMultiplier(newDamageMultiplier);
}

bool LivingEntity::getTeam() const
{
	return isAlly;
}

bool LivingEntity::takeDamage(float damageValue) 
{
	float currentHealth = stats.getCurrentHealth();

	if (currentHealth - damageValue < 0)
	{
		setActive(false);
		return true;
	}

	stats.setCurrentHealth(currentHealth - damageValue);
	return false;
}
