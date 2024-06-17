#pragma once
#include "LivingEntity.h"
#include <string>

class Player : public LivingEntity {
private:
	bool movingUp{ false };
	bool movingDown{ false };
	bool movingLeft{ false };
	bool movingRight{ false };

	int level{ 1 };
	float experience{ 0 };

	int money;

	std::array<float, 20> experienceRequierement;

public:
	Player(const std::string& filePath, const std::string& saveFile);
	
	void levelUp();
	void heal(float healValue);
	void giveExperience(float experienceValue);
	void giveMoney(int moneyValue);

	float getExperience() const;
	float getExperienceRequierment() const;
	int getMoney() const;

	int getLevel() const;

	void update(sf::Time elapsedTime) override;
	void checkBounds(sf::Vector2f stageSize) override;
	void handleInput(sf::Keyboard::Key key, bool isPressed);
	void shoot(sf::Vector2f projDirection) override;
};
