#include "Stage.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Stage::Stage(std::string_view name) : name{ name }
{
	std::ifstream f("resources/Stage.json");
	json allData = json::parse(f);
	json stageData = allData.at(name);

	size = sf::Vector2f(stageData.at("length"), stageData.at("height"));
	totalWaveNumber = stageData.at("totalWaveNumber");

	/* test pour afficher le stage */
	texture.loadFromFile("resources/sprites/floor.png");
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(sf::Vector2f(size.x / texture.getSize().x, size.y / texture.getSize().y));
}

void Stage::update(sf::Time elapsedTime, sf::RenderWindow const& gameWindow)
{
	/* Spawning the Enemies */
	if (isWaveBeginning)
	{
		if (currentWaveNumber < totalWaveNumber)
		{
			currentWaveNumber++;
			currentSubWaveNumber = 1;
			spawn();
			isWaveBeginning = false;
			subwaveTimer.restart(); // Start timer for subwave delay
		}
	}
	else if (subwaveTimer.getElapsedTime().asSeconds() >= 10.0f)
	{
		// Check if all enemies from previous subwave are inactive before spawning next
		bool allInactive = true;
		for (const auto& enemy : enemies) {
			if (enemy->getActive()) {
				allInactive = false;
				break;
			}
		}
		if (allInactive)
		{
			std::ifstream f("resources/Stage.json");
			json allData = json::parse(f);

			json waveData = allData.at(name).at(std::format("wave_{}", currentWaveNumber));

			if (waveData.contains(std::format("sub_wave_{}", currentSubWaveNumber + 1)))
			{
				currentSubWaveNumber++;
				spawn();
				subwaveTimer.restart();
			}
			else if (currentWaveNumber < totalWaveNumber)
			{
				currentWaveNumber++;
				currentSubWaveNumber = 1;
				spawn();
				subwaveTimer.restart();
			}
		}
	}

	/* Update the player */
	updatePlayer(elapsedTime, gameWindow);

	/* Update the enemies */
	updateEnemies(elapsedTime);

	/* Update the collectibles */
	updateCollectibles(elapsedTime);
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

		for (const auto& projectile : player->getProjectiles()) {
			if (projectile->getActive()) {
				projectile->update(elapsedTime);
				projectile->checkBounds(size);
				playerProjectileCheckCollisions(*projectile);
			}
		}
	}
}

void Stage::updateEnemies(sf::Time elapsedTime) const
{
	for (const auto& enemy : enemies) {
		if (enemy->getActive()) {
			enemy->update(elapsedTime); /*  the position and the shooting */
			enemy->checkBounds(size);

			for (const auto& projectile : enemy->getProjectiles()) {
				if (projectile->getActive()) {
					projectile->update(elapsedTime);
					projectile->checkBounds(size);
					enemyProjectileCheckCollisions(*projectile);
				}
			}
		}
	}
}

void Stage::updateCollectibles(sf::Time elapsedTime)
{
	for (const auto& collectible : collectibles)
	{
		if (collectible->getActive()) {
			collectible->update(elapsedTime);
			collectibleCheckCollision();
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

void Stage::render(sf::RenderWindow& gameWindow) const
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
	
}

void Stage::setPlayer(std::shared_ptr<Player> setPlayer)
{
	player = setPlayer;
	player->setPosition(sf::Vector2f(size.x/2 - player->getSize().x/2, size.y/2 - player->getSize().y/2));
}

void Stage::spawn()
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

void Stage::playerAutoFire(sf::RenderWindow const& gameWindow) const
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
}

void Stage::enemyProjectileCheckCollisions(Projectile& projectile) const
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
				if (std::optional<Collectible> dropedCollectible = enemy->dropCollectible(); dropedCollectible.has_value()) {
					collectibles.push_back(std::make_unique<Collectible>(dropedCollectible.value()));
				}
			}
		}
	}
}

void Stage::collectibleCheckCollision() {
	for (auto const& collectible : collectibles) {
		if (collectible->getGlobalBounds().intersects(player->getGlobalBounds()))
		{
			switch (collectible->getCollectibleType())
			{
			case CollectibleType::money:
				money += static_cast<int>(collectible->getCollectibleValue());
				break;
			case CollectibleType::health:
				player->heal(collectible->getCollectibleValue());
				break;
			case CollectibleType::experience:
				player->giveExperience(collectible->getCollectibleValue());
				break;
			}
			collectible->setActive(false);
		}
	}
}
