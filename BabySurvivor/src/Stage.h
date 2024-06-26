#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "SoundManager.h"

class Stage {
private:
	std::string name;
	sf::Vector2f size;

	int totalWaveNumber = 0;
	int currentWaveNumber = 2;
	int currentSubWaveNumber = 0;
	sf::Clock subwaveTimer;
	bool isWaveBeginning = true;
	bool isSubWaveBeginning = true;

	std::shared_ptr<Player> player;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Collectible>> collectibles;

	SoundManager soundManager;

	/* Regroup to an eventual other class UI */
	sf::Font font;
	sf::Text hpText;
	sf::RectangleShape hpBar;
	sf::Text levelText;
	sf::Text moneyText;
	sf::Text waveText;
	sf::Text xpText;
	sf::RectangleShape xpBar;

	int frameCounter = 0;

	sf::Sprite sprite{};
	sf::Texture texture;

	void updateJsonMoney() const;

	//ADDED LAST MINUTE :
	bool initialDelayDone = false;
	sf::Clock initialDelayTimer;

public:
	explicit Stage(std::string_view name);

	void setPlayer(std::shared_ptr<Player> setPlayer);
	void handleInput(sf::Keyboard::Key key, bool isPressed);

	int update(sf::Time elapsedTime, sf::RenderWindow const& gameWindow);
	void updatePlayer(sf::Time elapsedTime, sf::RenderWindow const& gameWindow);
	void updateEnemies(sf::Time elapsedTime);
	void updateCollectibles(sf::Time elapsedTime);
	sf::FloatRect updateView(sf::RenderWindow const& gameWindow) const;

	void spawnWave();
	void spawnSubWave();

	void playerAutoFire(sf::RenderWindow const& gameWindow);

	void enemyPlayerCheckCollisions(Enemy const& enemy) const;
	void enemyProjectileCheckCollisions(Projectile& projectile);
	void playerProjectileCheckCollisions(Projectile& projectile);
	void collectibleCheckCollisions();

	void render(sf::RenderWindow& gameWindow);
	void renderHpBar(sf::RenderWindow& gameWindow);
	void renderXpBar(sf::RenderWindow& gameWindow);
	void renderLevelMoney(sf::RenderWindow& gameWindow);

	void changeVolume(int newVolumeLevel);

	void startStage();
	/* Method used only for testing purposes */
	sf::Vector2f getSize() const;
	bool hasEnemies() const;
	void killEnemies() const;
	int getCurrentWave() const;
	void addCollectible(Collectible newCollectible);
	void addEnemy(Enemy&& newEnemy);
	float getEnemyHealth(int enemyIndex);
	bool getIsWaveBeginning() const;
	void setInitialDelayDone(bool initialDelay);
};
