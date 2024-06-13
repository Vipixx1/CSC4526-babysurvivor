#include "Stage.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Stage::Stage(std::string_view name, sf::RenderWindow& gameWindow) : name{ name }
{
	std::ifstream f("resources/Stage.json");
	json allData = json::parse(f);
	json stageData = allData.at("level_1");

	size = sf::Vector2f(stageData.at("length") * gameWindow.getSize().x, stageData.at("height") * gameWindow.getSize().y);
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
