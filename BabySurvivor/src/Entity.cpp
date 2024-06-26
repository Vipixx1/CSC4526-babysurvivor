#include "Entity.h"
#include <fstream>

using json = nlohmann::json;

Entity::Entity(const std::string& filePath, const std::string& entityName)
{
	std::ifstream f(filePath);
	json allData = json::parse(f);

	json entityData = allData.at(entityName);

	length = entityData.at("length");
	height = entityData.at("height");

	entityBox.setFillColor(sf::Color::White);
	entityBox.setSize(sf::Vector2f(length, height));

	spriteFile = entityData.at("sprite");

	texture.loadFromFile(spriteFile);
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(sf::Vector2f(entityBox.getSize().x / static_cast<float>(texture.getSize().x), entityBox.getSize().y / static_cast<float>(texture.getSize().y)));
}

sf::Vector2f Entity::getPosition() const
{
	return entityBox.getPosition();
}

void Entity::setPosition(const sf::Vector2f& position)
{
	entityBox.setPosition(position);
	sprite.setPosition(position);
}

sf::Vector2f Entity::getSize() const
{
	return entityBox.getSize();
}

bool Entity::getActive() const
{
	return isActive;
}

void Entity::setActive(bool active)
{
	isActive = active;
}

sf::FloatRect Entity::getGlobalBounds() const
{
	return entityBox.getGlobalBounds();
}

void Entity::render(sf::RenderWindow& gameWindow) const
{
	gameWindow.draw(sprite);
}

void Entity::checkBounds(sf::Vector2f stageSize)
{
	sf::Vector2f position = getPosition();
	sf::Vector2f size = getSize();

	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	if (position.x + size.x > stageSize.x) position.x = stageSize.x - size.x;
	if (position.y + size.y > stageSize.y) position.y = stageSize.y - size.y;

	setPosition(position);
}

void Entity::moveEntity(sf::Vector2f direction)
{
	entityBox.move(direction);
	sprite.move(direction);
}
