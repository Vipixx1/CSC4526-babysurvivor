#include "Player.h"

Player::Player(const std::string& filePath, sf::Vector2f coords) :
	LivingEntity{ filePath, coords }
{}

void Player::levelUp() 
{
	level++;
}
