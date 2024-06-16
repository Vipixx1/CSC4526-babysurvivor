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
	Projectile newProjectile{ "resources/Entity.json", getCoords() + sf::Vector2f(getSize().x / 2, getSize().y / 2), velocity, stats.getDamage(), isAlly};
	return newProjectile;
}

bool LivingEntity::isDead() const
{
	return dead;
}

void LivingEntity::kill() {
	dead = true;
}