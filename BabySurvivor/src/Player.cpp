#include "Player.h"

Player::Player(const std::string& filePath, sf::Vector2f coords, const float length, const float height, int level) :
	LivingEntity{ filePath, coords, length, height },
	level{ level } {}

void Player::levelUp() 
{
	level++;
}
