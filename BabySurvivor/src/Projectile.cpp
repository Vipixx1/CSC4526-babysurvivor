#include "Projectile.h"

Projectile::Projectile(const std::string& filePath, const std::string& entity, float damage, bool isAlly) :
	Entity{ filePath, entity },
	damage{ damage },
	isAlly{ isAlly } 
{}

void Projectile::update(sf::Time elapsedTime)
{
	/* Update the projectile's movement */
	moveEntity(getDirection() * elapsedTime.asSeconds());

	/* Other eventual updates */
}

void Projectile::checkBounds(sf::Vector2f stageSize)
{
	sf::Vector2f position = getPosition();

	if (sf::Vector2f size = getSize(); 
		position.x + size.x < 0 || 
		position.y + size.y < 0 ||
		position.x + size.x > stageSize.x || 
		position.y + size.y > stageSize.y)
	{
		setActive(false);
	}
	setPosition(position);
}

bool Projectile::getTeam() const
{
	return isAlly;
}

sf::Vector2f Projectile::getDirection() const
{
	return direction;
}

void Projectile::setDirection(sf::Vector2f newDirection)
{
	direction = newDirection;
}

float Projectile::getDamage() const
{
	return damage;
}

