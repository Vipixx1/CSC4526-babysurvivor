#include "Collectible.h"

Collectible::Collectible(const std::string& filePath, const std::string& entityName, CollectibleType type, float value) :
	Entity{ filePath, entityName },
	type{ type },
	value{ value } {}

void Collectible::update(sf::Time elapsedTime, sf::Vector2f stageSize)
{
	//DO NOTHING YET
}


CollectibleType Collectible::getCollectibleType() const
{
	return type;
}

float Collectible::getCollectibleValue() const
{
	return value;
}
