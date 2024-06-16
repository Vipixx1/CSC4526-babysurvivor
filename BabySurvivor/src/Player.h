#pragma once
#include "LivingEntity.h"
#include <string>

class Player : public LivingEntity {
private:
	int level = 1;
	bool movingUp{ false };
	bool movingDown{ false };
	bool movingLeft{ false };
	bool movingRight{ false };

public:
	Player(const std::string& filePath, const std::string& saveFile);
	void levelUp();
	void update(sf::Time elapsedTime) override;
	void checkBounds(sf::Vector2f stageSize) override;
	void handleInput(sf::Keyboard::Key key, bool isPressed);
	void shoot(sf::Vector2f projDirection) override;
};