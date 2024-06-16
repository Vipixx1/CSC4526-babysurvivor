#pragma once

#include "LivingEntity.h"
#include <string>

class Player : public LivingEntity {
private:
	int level{ 1 };
	float experience{ 0 };
	float nextLevelExperience{ 100 };

	std::array<float, 20> experienceRequierment;

public:
	Player(const std::string& filePath, const std::string& saveFile, sf::Vector2f coords);
	void levelUp();

	void heal(float healValue);
	void giveExperience(float experienceValue);
};