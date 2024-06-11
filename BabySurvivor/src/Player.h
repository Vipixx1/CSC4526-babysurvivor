#pragma once

#include "Entity.h"

class Player : public Entity {
private:
	int level;

public:
	Player();
	void levelUp();
};