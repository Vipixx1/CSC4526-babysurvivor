#include "Enemy.h"

Enemy::Enemy(const std::string& filePath, sf::Vector2f coords, EnemyType enemyType, int waveNumber) :
	enemyType{ enemyType },
	LivingEntity{ filePath, enemyTypeMap.find(enemyType)->second, coords}
{}
