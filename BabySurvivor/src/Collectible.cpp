#include "Collectible.h"

Collectible::Collectible(const std::string& filePath, const std::string& entityName, CollectibleType type, float value) :
	Entity{filePath, entityName },
	type{type},
	value{value} {}


float Collectible::collect() const
{
	return value;
}

//Collectible Collectible::drop(const std::string& entityName, sf::Vector2f coords, CollectibleType type, float value)
//{
//	Collectible newCollectible{ "resources/Entity.json", entityName, coords, type, value };
//	return newCollectible;
//}