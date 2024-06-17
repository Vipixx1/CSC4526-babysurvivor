#include "Player.h"
#include <iostream>

Player::Player(const std::string& filePath, const std::string& saveFile) :
	LivingEntity{ filePath, saveFile, true }
{}

void Player::levelUp()
{
	std::cout << "Level up!" << std::endl;

	// Does the actual level up and update the experience requierment for the next level
	level++;
	nextLevelExperienceRequierement = experienceRequierement[level-1];

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
	if ((experience + experienceValue) >= nextLevelExperienceRequierement)
	{
		experience = (experience + experienceValue) - nextLevelExperienceRequierement;
		levelUp();
	}

	else
	{
		experience += experienceValue;
	}
}

void Player::update(sf::Time elapsedTime)
{
	sf::Vector2f velocity(0.f, 0.f);
	float speed = getSpeed();
	sf::Vector2f position = getPosition();

	if (movingUp)	velocity.y -= speed;
	if (movingDown)	velocity.y += speed;
	if (movingLeft)	velocity.x -= speed;
	if (movingRight)velocity.x += speed;

	sf::Vector2f newPosition = position + velocity * elapsedTime.asSeconds();

	setPosition(newPosition);
}

void Player::checkBounds(sf::Vector2f stageSize)
{
	sf::Vector2f position = getPosition();
	sf::Vector2f size = getSize();

	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	if (position.x + size.x > stageSize.x) position.x = stageSize.x - size.x;
	if (position.y + size.y > stageSize.y) position.y = stageSize.y - size.y;

	setPosition(position);
}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Z)
		movingUp = isPressed;
	else if (key == sf::Keyboard::S)
		movingDown = isPressed;
	else if (key == sf::Keyboard::Q)
		movingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		movingRight = isPressed;
}

void Player::shoot(sf::Vector2f projDirection)
{
	auto newProjectile = std::make_shared<Projectile>("resources/Entity.json", getDamage(), true);
	newProjectile->setPosition(getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2));
	newProjectile->setDirection(projDirection);
	getProjectiles().push_back(newProjectile);}
