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

	/* test pour afficher le stage */
	texture.loadFromFile("resources/sprites/floor.png");
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(sf::Vector2f(size.x / texture.getSize().x, size.y / texture.getSize().y));
	
}

void Stage::render(sf::RenderWindow& gameWindow) const
{
	gameWindow.draw(sprite);
}

std::vector<std::unique_ptr<Enemy>> Stage::spawn()
{
	std::ifstream f("resources/Stage.json");
	json allData = json::parse(f);

	json waveData = allData.at(name).at(std::format("wave_{}", waveNumber));

	std::vector<std::unique_ptr<Enemy>> wave;

	for (int i = 1; i <= waveData.at("totalEnemyNumber"); i++) {
		json enemyData = waveData.at(std::format("enemy_{}", i));
		auto enemy = std::make_unique<Enemy>("resources/Entity.json", enemyData.at("type"), sf::Vector2f(enemyData.at("coords_spawn_x"), enemyData.at("coords_spawn_y")));
		wave.push_back(std::move(enemy));
	}

	return wave;
}

void Stage::setWaveNumber(int newWaveNumber)
{
	waveNumber = newWaveNumber;
}

sf::Vector2f Stage::getSize() const
{
	return size;
}

bool Stage::getSpawningBool()
{
	return isWaveBeginning;
}

void Stage::setSpawningBool(bool newIsWaveBeginning)
{
	this->isWaveBeginning = isWaveBeginning;
}
