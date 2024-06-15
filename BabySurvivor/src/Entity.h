#pragma once
#include <SFML/Graphics.hpp>
#include <json.hpp>

class Entity {
private:
	sf::RectangleShape entityBox;
	float length;
	float height;

public:
	explicit Entity(const std::string& filePath, const std::string& entityName, sf::Vector2f coords);

	sf::Vector2f getCoords() const;
	void setCoords(const sf::Vector2f& position);

	sf::Vector2f getSize() const;

	sf::FloatRect getGlobalBounds() const;

	void render(sf::RenderWindow& gameWindow) const;
	void moveEntity(sf::Vector2f movement);
};