#pragma once

#include "LivingEntity.h"
#include <string>

class Player : public LivingEntity {
private:
	int level = 1;

public:
	Player(const std::string& filePath, sf::Vector2f coords);
	void levelUp();
};