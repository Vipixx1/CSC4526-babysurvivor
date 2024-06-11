#pragma once

#include <SFML/Graphics.hpp>

class Projectile {
private:
	sf::Vector2f coords;
	float damage;
	bool isAlly;

public:
	explicit Projectile(sf::Vector2f coords, float damage, bool isAlly);
};