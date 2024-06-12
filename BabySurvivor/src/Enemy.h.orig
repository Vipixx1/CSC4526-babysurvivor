#pragma once
#include "LivingEntity.h"
#include <string>

enum class EnemyType {
	broccoli_v1,
	broccoli_v2,
	tomato_v1,
	tomato_v2,
	spider_v1,
	ladybug_v1,
	ladybug_v2,
	robotToy_v1,
	robotToy_v2,
	towerToy_v1,
	towerToy_v2,
	towerToy_v3,
	towerToy_v4
};

class Enemy : public LivingEntity {
private:
	std::string enemyType;

public:
	Enemy(const std::string& filePath, const std::string& enemyType, sf::Vector2f coords);
};



