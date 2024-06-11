#pragma once

#include "LivingEntity.h"
#include <string>

class Player : public LivingEntity {
private:
	int level;

public:
	Player(const std::string& filePath, sf::Vector2f coords, const float length, const float height, int level);
	void levelUp();
};