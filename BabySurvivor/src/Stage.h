#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"

class Stage {
private:
	std::string name;
	sf::Vector2f size;
	int waveNumber = 1;
	bool isWaveBeginning = true;

	std::shared_ptr<Player> player;
	std::vector<std::unique_ptr<Enemy>> enemies;
	int frameCounter = 0;

public:
	/* test pour afficher les sprites */
	sf::Sprite sprite{};
	sf::Texture texture;

	explicit Stage(std::string_view name);

	void update(sf::Time elapsedTime, sf::RenderWindow const& gameWindow);
	void render(sf::RenderWindow& gameWindow) const;

	void setPlayer(std::shared_ptr<Player> setPlayer);
	void spawn();
	void playerAutoFire(sf::RenderWindow const& gameWindow) const;
	sf::FloatRect updateView(sf::RenderWindow const& gameWindow) const;

	void enemyProjectileCheckCollisions(Projectile& projectile) const;
	void playerProjectileCheckCollisions(Projectile& projectile) const;

};