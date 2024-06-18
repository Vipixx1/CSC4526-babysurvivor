#include "Stage.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

Stage::Stage(std::string_view name) : name{ name }
{
	std::ifstream f("resources/Stage.json");
	json allData = json::parse(f);
	f.close();
	json stageData = allData.at(name);

	size = sf::Vector2f(stageData.at("length"), stageData.at("height"));
	totalWaveNumber = stageData.at("totalWaveNumber");

	texture.loadFromFile("resources/sprites/floor.png");
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(sf::Vector2f(size.x / static_cast<float>(texture.getSize().x), size.y / static_cast<float>(texture.getSize().y)));

	font.loadFromFile("resources/Sansation.ttf");
	xpText.setFont(font);
	hpText.setFont(font);
	moneyText.setFont(font);
	levelText.setFont(font);
	waveText.setFont(font);
}

/***
 * Using a shared_ptr instead of a unique_ptr for the tests only
 * so there is no problem of moving ptr, and callin them in the test...
 ***/
void Stage::setPlayer(std::shared_ptr<Player> setPlayer)
{
	player = std::move(setPlayer);
	player->setPosition(sf::Vector2f(size.x / 2 - player->getSize().x / 2, size.y / 2 - player->getSize().y / 2));
}

void Stage::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	player->handleInput(key, isPressed);

}

void Stage::updateJsonMoney() const
{
	int newMoney = player->getMoney();
	std::string saveFileName = player->getSaveFileName();

	std::ifstream f("resources/Entity.json");
	json allData = json::parse(f);
	f.close();

	allData[saveFileName]["money"] = newMoney;

	std::ofstream fout("resources/Entity.json");
	fout << allData.dump(4);

	fout.flush();
	fout.close();
}


int Stage::update(sf::Time elapsedTime, sf::RenderWindow const& gameWindow)
{
	if (player->getCurrentHealth() <= 0)
	{
		updateJsonMoney();
		return 1;
	}

	if (currentWaveNumber == totalWaveNumber && enemies.empty())
	{
		updateJsonMoney();
		return 2;
	}
	/* Update the spawning */
	spawnWave();

	/* Update the player */
	updatePlayer(elapsedTime, gameWindow);

	/* Update the enemies */
	updateEnemies(elapsedTime);

	/* Update the collectibles */
	updateCollectibles(elapsedTime);

	return -1;
}

void Stage::updatePlayer(sf::Time elapsedTime, sf::RenderWindow const& gameWindow) 
{
	if (player->getActive()) {
		player->update(elapsedTime);
		player->checkBounds(size);

		frameCounter++;

		// Auto fire every 30 frames
		if (static_cast<float>(frameCounter) >= player->getShotDelay()) {
			
			playerAutoFire(gameWindow);
			

			// Play the shoot sound
			// soundManager.playSound("resources/audio/playerShoot.wav"); // Uncomment this line if soundManager is defined

			// Reset the frame counter
			frameCounter = 0;
		}

		// Update and check collisions for projectiles
		auto& projectiles = player->getProjectiles();
		for (auto it = projectiles.begin(); it != projectiles.end();) {
			auto& projectile = **it;  // Dereference std::unique_ptr

			if (projectile.getActive()) {
				projectile.update(elapsedTime);
				projectile.checkBounds(size);
				playerProjectileCheckCollisions(projectile);
				++it;
			}
			else {
				// Remove inactive projectile by dereferencing and erasing from vector
				it = projectiles.erase(it);
			}
		}
	}
}

void Stage::updateEnemies(sf::Time elapsedTime) 
{
	for (auto it = enemies.begin(); it != enemies.end();) {
		auto const& enemy = *it;  // Dereference std::unique_ptr

		if (enemy->getActive()) {
			enemy->update(elapsedTime);
			
			enemy->checkBounds(size);
			enemyPlayerCheckCollisions(*enemy);

			// Handle enemy projectiles similarly if needed
			auto& projectiles = enemy->getProjectiles();
			for (auto itP = projectiles.begin(); itP != projectiles.end();) {
				auto& projectile = **itP;  // Dereference std::unique_ptr

				if (projectile.getActive()) {
					projectile.update(elapsedTime);
					projectile.checkBounds(size);
					enemyProjectileCheckCollisions(projectile);
					++itP;
				}
				else {
					// Remove inactive projectile by dereferencing and erasing from vector
					itP = projectiles.erase(itP);
				}
			}
			++it;  // Move to the next enemy
		}
		else {
			// Remove inactive enemy by erasing from vector
			it = enemies.erase(it);
		}
	}
}

void Stage::updateCollectibles(sf::Time elapsedTime)
{
	for (const auto& collectible : collectibles)
	{
		if (collectible->getActive()) {
			collectible->update(elapsedTime);
			collectibleCheckCollisions();
		}
	}
}

sf::FloatRect Stage::updateView(sf::RenderWindow const& gameWindow) const
{
	sf::Vector2f cameraPosition{ 0, 0 };
	/* Make the camera follow the player */
	cameraPosition.x = player->getPosition().x + (player->getSize().x / 2) - (static_cast<float>(gameWindow.getSize().x) / 2);
	cameraPosition.y = player->getPosition().y + (player->getSize().y / 2) - (static_cast<float>(gameWindow.getSize().y) / 2);
	/* Check if the camera is within the stage borders*/
	if (cameraPosition.x < 0) cameraPosition.x = 0;
	if (cameraPosition.x + static_cast<float>(gameWindow.getSize().x) > size.x) cameraPosition.x = size.x - static_cast<float>(gameWindow.getSize().x);
	if (cameraPosition.y < 0) cameraPosition.y = 0;
	if (cameraPosition.y + static_cast<float>(gameWindow.getSize().y) > size.y) cameraPosition.y = size.y - static_cast<float>(gameWindow.getSize().y);

	return sf::FloatRect(cameraPosition.x, cameraPosition.y, static_cast<float>(gameWindow.getSize().x), static_cast<float>(gameWindow.getSize().y));
}


void Stage::spawnWave()
{
	if (isWaveBeginning)
	{
		if (currentWaveNumber < totalWaveNumber)
		{
			currentWaveNumber++;
			currentSubWaveNumber = 1;
			spawnSubWave();
			isWaveBeginning = false;
			subwaveTimer.restart(); // Start timer for subwave delay
		}
	}
	else
	{
		bool allInactive = true;
		for (const auto& enemy : enemies)
		{
			if (enemy->getActive())
			{
				allInactive = false;
				break;
			}
		}

		// Move to the next subwave if the timer has passed 10 seconds or all enemies are inactive
		if (subwaveTimer.getElapsedTime().asSeconds() >= 10.0f || allInactive)
		{
			std::ifstream f("resources/Stage.json");
			json allData = json::parse(f);

			json waveData = allData.at(name).at(std::format("wave_{}", currentWaveNumber));

			if (waveData.contains(std::format("sub_wave_{}", currentSubWaveNumber + 1)))
			{
				currentSubWaveNumber++;
				spawnSubWave();
				subwaveTimer.restart();
			}
			else if (allInactive && currentWaveNumber < totalWaveNumber)
			{
				// Only start a new wave if all enemies are inactive
				isWaveBeginning = true;
			}
		}
	}
}

void Stage::spawnSubWave()
{
	std::ifstream f("resources/Stage.json");
	json allData = json::parse(f);

	json waveData = allData.at(name).at(std::format("wave_{}", currentWaveNumber));
	json subWaveData = waveData.at(std::format("sub_wave_{}", currentSubWaveNumber));

	int totalEnemies = subWaveData.at("totalEnemyNumber");

	for (int i = 1; i <= totalEnemies; i++)
	{
		json enemyData = subWaveData.at(std::format("enemy_{}", i));
		auto enemy = std::make_unique<Enemy>("resources/Entity.json", enemyData.at("type"), *player);
		enemy->setPosition(sf::Vector2f(enemyData.at("coords_spawn_x"), enemyData.at("coords_spawn_y")));
		enemies.push_back(std::move(enemy));
	}
}


void Stage::playerAutoFire(sf::RenderWindow const& gameWindow)
{
	// Get the mouse position in the window
	sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
	// Convert it to world coordinates
	sf::Vector2f direction = gameWindow.mapPixelToCoords(mousePos);

	// Calculate direction and normalize
	direction = direction - (player->getPosition() + sf::Vector2f(player->getSize().x/2, player->getSize().y/2));
	direction = direction * player->getShotSpeed() / sqrt(direction.x * direction.x + direction.y * direction.y);

	// Create and shoot a new projectile
	player->shoot(direction);

	soundManager.playSound(0);
}


void Stage::enemyPlayerCheckCollisions(Enemy const& enemy) const
{
	if (player->getActive() && enemy.getGlobalBounds().intersects(player->getGlobalBounds())) {
		player->takeDamage(enemy.getDamage());
	}
}

void Stage::enemyProjectileCheckCollisions(Projectile& projectile)
{
	if (player->getActive() && player->getTeam() != projectile.getTeam() && projectile.getGlobalBounds().intersects(player->getGlobalBounds())) {
		player->takeDamage(projectile.getDamage());
		projectile.setActive(false);
	}
}

void Stage::playerProjectileCheckCollisions(Projectile& projectile) {
	for (auto const& enemy : enemies) {
		if (enemy->getActive() && enemy->getTeam() != projectile.getTeam() && projectile.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
			projectile.setActive(false);
			if (enemy->takeDamage(projectile.getDamage())) { // takeDamage returns true if the enemy is dead
				if (player->giveExperience(2.f)) { soundManager.playSound(4); }
				if (std::optional<std::unique_ptr<Collectible>> dropedCollectible = enemy->dropCollectible(); dropedCollectible.has_value()) {
					collectibles.push_back(std::move(dropedCollectible.value()));
				}
			}
		}
	}
}

void Stage::collectibleCheckCollisions() {
	using enum CollectibleType;

	for (auto const& collectible : collectibles) {
		if (collectible->getActive() && collectible->getGlobalBounds().intersects(player->getGlobalBounds()))
		{
			collectible->setActive(false);
			switch (collectible->getCollectibleType())
			{
			case money:
				collectible->setActive(false);
				player->giveMoney(static_cast<int>(collectible->getCollectibleValue()));
				soundManager.playSound(2);
				break;
			case health:
				collectible->setActive(false);
				player->heal(collectible->getCollectibleValue());
				soundManager.playSound(1);
				break;
			case experience:
				collectible->setActive(false);
				if (player->getLevel() < 20) 
				{
					// We play the level up sound effect when needed
					if (player->giveExperience(collectible->getCollectibleValue())) { soundManager.playSound(4); }
					soundManager.playSound(3);
				}
				
				break;
			}
		}
	}
}


void Stage::render(sf::RenderWindow& gameWindow)
{
	gameWindow.clear(sf::Color::Black);

	gameWindow.draw(sprite);

	if (player->getActive()) {
		player->render(gameWindow);
		for (const auto& projectile : player->getProjectiles())
		{
			if (projectile->getActive())
				projectile->render(gameWindow);
		}
	}


	for (const auto& enemy : enemies)
	{
		if (enemy->getActive()) {
			enemy->render(gameWindow);
			for (const auto& projectile : enemy->getProjectiles())
			{
				if (projectile->getActive())
					projectile->render(gameWindow);
			}
		}
	}

	for (const auto& collectible : collectibles)
	{
		if (collectible->getActive())
			collectible->render(gameWindow);
	}

	renderHpBar(gameWindow);
	renderXpBar(gameWindow);
}

void Stage::renderHpBar(sf::RenderWindow& gameWindow)
{
	sf::View view = gameWindow.getView();
	float x0 = view.getCenter().x;
	float y0 = view.getCenter().y;

	hpText.setString(std::format("Health {}/{}", player->getCurrentHealth(), player->getMaxHealth()));
	hpText.setCharacterSize(27);
	hpText.setFillColor(sf::Color::Black);
	hpText.setPosition(x0 - 130, y0 + 380);

	hpBar.setPosition(x0 - hpBar.getSize().x/2, y0 + 380);
	hpBar.setSize(sf::Vector2f(500.f, 30.f));
	hpBar.setFillColor(sf::Color::Red);

	gameWindow.draw(hpBar);
	gameWindow.draw(hpText);
}

void Stage::renderXpBar(sf::RenderWindow& gameWindow)
{
	sf::View view = gameWindow.getView();
	float x0 = view.getCenter().x;
	float y0 = view.getCenter().y;

	xpText.setString(std::format("EXP {}/{}", player->getExperience(), player->getExperienceRequierment()));
	xpText.setCharacterSize(27);
	xpText.setFillColor(sf::Color::Black);
	xpText.setPosition(sf::Vector2f(x0 - 130, y0 + 420));

	xpBar.setPosition(sf::Vector2f(x0 - xpBar.getSize().x / 2, y0 + 420));
	xpBar.setSize(sf::Vector2f(500.f, 30.f));
	xpBar.setFillColor(sf::Color::Blue);

	gameWindow.draw(xpBar);
	gameWindow.draw(xpText);
}

void Stage::renderLevelMoney(sf::RenderWindow& gameWindow)
{
	sf::View view = gameWindow.getView();
	float x = view.getCenter().x;
	float y = view.getCenter().y;

	levelText.setString(std::format("Level: {}", player->getLevel()));
	levelText.setCharacterSize(30);
	levelText.setFillColor(sf::Color::Black);
	levelText.setPosition(sf::Vector2f(x + 750, y - 500));

	waveText.setString(std::format("Wave: {}/{}", currentWaveNumber, totalWaveNumber));
	waveText.setCharacterSize(30);
	waveText.setFillColor(sf::Color::Black);
	waveText.setPosition(sf::Vector2f(x - 50, y - 500));

	moneyText.setString(std::format("Money: {}", player->getMoney()));
	moneyText.setCharacterSize(30);
	moneyText.setFillColor(sf::Color::Black);
	moneyText.setPosition(sf::Vector2f(x + 750, y - 460));

	gameWindow.draw(levelText);
	gameWindow.draw(moneyText);
	gameWindow.draw(waveText);
}


void Stage::changeVolume(int newVolumeLevel)
{
	soundManager.changeVolume(newVolumeLevel);
}


/* unitTests purpose : */

void Stage::addCollectible(Collectible newCollectible)
{
	collectibles.push_back(std::make_unique<Collectible>(newCollectible));
}

void Stage::addEnemy(Enemy&& newEnemy)
{
	enemies.push_back(std::make_unique<Enemy>(std::move(newEnemy)));
}

float Stage::getEnemyHealth(int enemyIndex)
{
	return enemies[enemyIndex].get()->getCurrentHealth();
}

bool Stage::getIsWaveBeginning() const
{
	return isWaveBeginning;
}

sf::Vector2f Stage::getSize() const
{
	return size;
}

bool Stage::hasEnemies() const
{
	return !enemies.empty();
}

void Stage::killEnemies() const
{
	for (auto const& enemy : enemies)
	{
		enemy->setActive(false);
	}
}

int Stage::getCurrentWave() const
{
	return currentWaveNumber;
}
