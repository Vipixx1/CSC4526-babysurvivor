#pragma once
#include <SFML/Graphics.hpp>

class Entity {
private:
	sf::RectangleShape entityBox;

public:
	explicit Entity(sf::Vector2f coords, const float lenght, const float height);
	sf::Vector2f getCoords() const;
	void render(sf::RenderWindow& gameWindow) const;
	void moveEntity(sf::Vector2f movement);
};