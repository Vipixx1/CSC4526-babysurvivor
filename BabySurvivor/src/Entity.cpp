#include "Entity.h"
#include <fstream>

using json = nlohmann::json;

Entity::Entity(const std::string& filePath, const std::string& entityName, sf::Vector2f coords)
{
	std::ifstream f(filePath);
	json allData = json::parse(f);

	json entityData = allData.at(entityName);

	length = entityData.at("length");
	height = entityData.at("height");

	entityBox.setPosition(coords);
	entityBox.setFillColor(sf::Color::White);
	entityBox.setSize(sf::Vector2f(length, height));
}

sf::Vector2f Entity::getCoords() const
{
	return entityBox.getPosition();
}

void Entity::render(sf::RenderWindow& gameWindow) const
{
	gameWindow.draw(entityBox);
}

void Entity::moveEntity(sf::Vector2f movement)
{
	entityBox.move(movement);
}
