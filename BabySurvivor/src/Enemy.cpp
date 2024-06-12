#include "Enemy.h"

Enemy::Enemy(const std::string& filePath, const std::string& enemyType, sf::Vector2f coords) :
	LivingEntity{ filePath, enemyType, coords},
	enemyType{ enemyType }
{

}
