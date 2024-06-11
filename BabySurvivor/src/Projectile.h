#pragma once

#include <SFML/Graphics.hpp>

class Projectile {
private:
	bool isAlly;
	int damage;
	sf::Vector2f coords;

public:
	void Projectile(sf::Vector2f coords, int damage, bool isAlly);
};