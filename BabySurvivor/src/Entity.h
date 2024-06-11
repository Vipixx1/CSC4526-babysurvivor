#pragma once
#include <SFML/Graphics.hpp>
#include "Stats.h"

class Entity {
private:
	sf::Vector2f coords;
	Stats stats;
	

public:
	sf::RectangleShape entityBox;
	
	Entity();
	void shoot();
	void takeDamage();
	void kill();

	float getSpeed();
};