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
	explicit Collectible(const std::string& filePath, const std::string& entityName, CollectibleType type, float value);
	void update(sf::Time elapsedTime) override;

	CollectibleType getCollectibleType() const;
	float getCollectibleValue() const;
};