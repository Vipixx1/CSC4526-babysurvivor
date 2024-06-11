#pragma once

#include "Entity.h"

class Player : public Entity {
private:
	int level;

public:
	void levelUp();
};