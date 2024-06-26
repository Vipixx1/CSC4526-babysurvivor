#pragma once
#include <SFML/Graphics.hpp>
#include <json.hpp>

class Entity {
private:
	sf::RectangleShape entityBox;
	float length;
	float height;
	bool isActive = true;

	std::string spriteFile;
	sf::Sprite sprite{};
	sf::Texture texture;

public:
	explicit Entity(const std::string& filePath, const std::string& entityName);
	Entity() = default;
	virtual ~Entity() = default;

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& position);
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getSize() const;
	bool getActive() const;
	void setActive(bool active);
	
	virtual void render(sf::RenderWindow& gameWindow) const;
	virtual void update(sf::Time elapsedTime, sf::Vector2f stageSize) = 0;
	virtual void checkBounds(sf::Vector2f stageSize);
	void moveEntity(sf::Vector2f direction);
};