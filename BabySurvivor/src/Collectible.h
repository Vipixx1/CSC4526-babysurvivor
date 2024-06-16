#pragma once

#include "Entity.h"

enum class CollectibleType {
	experience,
	health,
	money
};

class Collectible : public Entity {
private:
	CollectibleType type;
	float value;

public:
	explicit Collectible(const std::string& filePath, const std::string& entityName, sf::Vector2f coords, CollectibleType type, float value);

	CollectibleType getCollectibleType() const;
	float getCollectibleValue() const;

};