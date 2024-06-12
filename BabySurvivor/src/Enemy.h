#pragma once
#include "LivingEntity.h"
#include <string>
#include <unordered_map>

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
	EnemyType enemyType;
	const std::unordered_map<EnemyType, std::string> enemyTypeMap = {
		{ EnemyType::broccoli_v1, "broccoli_v1" },
		{ EnemyType::broccoli_v2, "broccoli_v2" },
		{ EnemyType::tomato_v1, "tomato_v1" },
		{ EnemyType::tomato_v2, "tomato_v2" },
		{ EnemyType::spider_v1, "spider_v1" },
		{ EnemyType::ladybug_v1, "ladybug_v1" },
		{ EnemyType::ladybug_v2, "ladybug_v2" },
		{ EnemyType::robotToy_v1, "robotToy_v1" },
		{ EnemyType::robotToy_v2, "robotToy_v2" },
		{ EnemyType::towerToy_v1, "towerToy_v1" },
		{ EnemyType::towerToy_v2, "towerToy_v2" },
		{ EnemyType::towerToy_v3, "towerToy_v3" },
		{ EnemyType::towerToy_v4, "towerToy_v4" }
	};

public:
	Enemy(const std::string& filePath, sf::Vector2f coords, EnemyType enemyType, int waveNumber);
};



