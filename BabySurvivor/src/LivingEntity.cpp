#include "LivingEntity.h"
#include <fstream>

using json = nlohmann::json;

LivingEntity::LivingEntity(const std::string& filePath, const std::string& livingEntityName, bool isAlly) :
	Entity{ filePath, livingEntityName },
	stats{ filePath, livingEntityName },
	isAlly{ isAlly }
{}

std::vector<std::unique_ptr<Projectile>>& LivingEntity::getProjectiles() 
{
	return projectiles;
}

std::unique_ptr<Projectile> LivingEntity::findInactiveProjectile()
{
	for (auto& projectile :projectiles) {
		if (!projectile->getActive()) {
			return std::move(projectile);
		}
	}
	return nullptr;
}

float LivingEntity::getSpeed() const
{
	return stats.getSpeed();
}

float LivingEntity::getCurrentHealth() const
{
	return stats.getCurrentHealth();
}

float LivingEntity::getMaxHealth() const
{
	return stats.getMaxHealth();
}

void LivingEntity::setMaxHealth(float newMaxHealth)
{
	stats.setMaxHealth(newMaxHealth);
}

void LivingEntity::setCurrentHealth(float newHealth)
{
	stats.setCurrentHealth(newHealth);
}

float LivingEntity::getDamage() const
{
	return stats.getDamage();
}

void LivingEntity::setDamage(float newDamage)
{
	stats.setDamage(newDamage);
}

float LivingEntity::getDamageMultiplier() const
{
	return stats.getDamageMultiplier();
}

void LivingEntity::setDamageMultiplier(float newDamageMultiplier)
{
	stats.setDamageMultiplier(newDamageMultiplier);
}

float LivingEntity::getShotDelay() const
{
	return stats.getShotDelay();
}

float LivingEntity::getShotSpeed() const
{
	return stats.getShotSpeed();

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
