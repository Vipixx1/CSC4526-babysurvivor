#include "Entity.h"

Entity::Entity(sf::Vector2f coords, const float length, const float height)
{
	entityBox.setPosition(coords);
	entityBox.setFillColor(sf::Color::Red);
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
