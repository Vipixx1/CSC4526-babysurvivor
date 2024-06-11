#pragma once

#include "LivingEntity.h"

class Player : public LivingEntity {
private:
	int level;

public:
	Player();
	void levelUp();
};