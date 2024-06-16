#include "Player.h"
#include <iostream>

Player::Player(const std::string& filePath, const std::string& saveFile, sf::Vector2f coords) :
	LivingEntity{ filePath, saveFile, coords }
{
	// Initialize the array containing the experience requierement for each level
	// The formulas are the one used in Minecraft
	for (int i = 0; i < 15; i++)
	{
		experienceRequierment[i] = static_cast<float>(2 * (i + 1) + 7);
	}

	for (int i = 15; i < 20; i++)
	{
		experienceRequierment[i] = static_cast<float>(5 * (i+1) - 38);
	}

	nextLevelExperienceRequierment = experienceRequierment[0];
}

void Player::levelUp() 
{
	std::cout << "Level up!" << std::endl;

	// Does the actual level up and update the experience requierment for the next level
	level++;
	nextLevelExperienceRequierment = experienceRequierment[level-1];

	// Boost player stat after each level up
	float currentMaxHealth = getMaxHealth();
	float currentDamage = getDamage();
	float currentDamageMultiplier = getDamageMultiplier();

	// We give 0.1 damage multiplier to the player each 5 levels
	if (level % 5 == 0)
	{
		setDamageMultiplier(currentDamageMultiplier + 0.1f);
	}

	// At each level we give a small boost in all player stats
	setMaxHealth(currentMaxHealth + 20);
	setDamage(currentDamage + 5);
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
	if ((experience + experienceValue) >= nextLevelExperienceRequierment)
	{
		experience = (experience + experienceValue) - nextLevelExperienceRequierment;
		levelUp();
	}

	else
	{
		experience += experienceValue;
	}
}
