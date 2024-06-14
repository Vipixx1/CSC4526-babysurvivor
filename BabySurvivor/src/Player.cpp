#include "Player.h"

Player::Player(const std::string& filePath, const std::string& saveFile, sf::Vector2f coords) :
	LivingEntity{ filePath, saveFile, coords }
{}

void Player::levelUp() 
{
	level++;
}
