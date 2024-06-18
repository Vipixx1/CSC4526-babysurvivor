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

	std::string saveFileName;

	int money;

	std::array<float, 20> experienceRequierement;

	bool isInvulnerable = false;
	const float invulnerabilityDuration = 1.0f;
	sf::Clock invulnerabilityTimer;
	
	bool isVisible = true;
	const float blinkInterval = 0.1f;
	sf::Clock blinkTimer;

public:
	Player(const std::string& filePath, const std::string& saveFile);
	
	void levelUp();
	void heal(float healValue);
	bool giveExperience(float experienceValue);
	void giveMoney(int moneyValue);

	float getExperience() const;
	float getExperienceRequierment() const;
	int getMoney() const;

	std::string getSaveFileName() const;

	int getLevel() const;

	bool takeDamage(float damageValue) override;
	void render(sf::RenderWindow& gameWindow) const override;
	void update(sf::Time elapsedTime) override;
	void checkBounds(sf::Vector2f stageSize) override;
	void handleInput(sf::Keyboard::Key key, bool isPressed);
	void shoot(sf::Vector2f projDirection) override;

};
