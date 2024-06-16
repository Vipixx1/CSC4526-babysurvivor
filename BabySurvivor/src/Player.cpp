#include "Player.h"

Player::Player(const std::string& filePath, const std::string& saveFile, sf::Vector2f coords) :
	LivingEntity{ filePath, saveFile, coords }
{}

void Player::levelUp() 
{
	level++;
	nextLevelExperience = 0;
}

void Player::heal(float healValue)
{
	float currentHealth = getCurrentHealth();
	float maxHealth = getMaxHealth();

	if (currentHealth + healValue >= maxHealth)
	{
		setCurrentHealth(maxHealth);
	}

	else
	{
		setCurrentHealth(currentHealth + healValue);
	}
}

void Player::giveExperience(float experienceValue)
{
	if ((experience + experienceValue) >= nextLevelExperience)
	{
		experience = (experience + experienceValue) - nextLevelExperience;
		levelUp();
	}

	else
	{
		experience += experienceValue;
	}
}
