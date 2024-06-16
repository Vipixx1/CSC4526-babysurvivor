#include "Collectible.h"

Collectible::Collectible(const std::string& filePath, const std::string& entityName, sf::Vector2f coords, CollectibleType type, float value) :
	Entity{filePath, entityName, coords},
	type{type},
	value{value} {}