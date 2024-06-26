#pragma once
#include "Entity.h"

class Projectile : public Entity {
private:
	sf::Vector2f direction;
	float damage;
	bool isAlly;

public:
	explicit Projectile(const std::string& filePath, const std::string& entity, float damage, bool isAlly);
	void update(sf::Time elapsedTime, sf::Vector2f stageSize) override;
	void checkBounds(sf::Vector2f stageSize) override;

	float getDamage() const;

	sf::Vector2f getDirection() const;
	void setDirection(sf::Vector2f newDirection);
	bool getTeam() const;
};