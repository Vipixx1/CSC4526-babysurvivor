#pragma once
#include <SFML/Graphics.hpp>
#include <json.hpp>

class Entity {
private:
	sf::RectangleShape entityBox;
	float length;
	float height;

public:
	explicit Entity(const std::string& filePath, sf::Vector2f coords);
	sf::Vector2f getCoords() const;
	void render(sf::RenderWindow& gameWindow) const;
	void moveEntity(sf::Vector2f movement);
};