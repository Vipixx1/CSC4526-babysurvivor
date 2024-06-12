#pragma once

#include "LivingEntity.h"
#include <string>

class Enemy : public LivingEntity {

public:
	Enemy(EnemyType enemyType, int waveNumber);
};

enum class EnemyType {
	Broccoli,
	Tomato,
	Spider,
	Ladybug,
	RobotToy,
	TowerToy
};