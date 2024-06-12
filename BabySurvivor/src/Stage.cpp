#include "Stage.h"

Stage::Stage(std::string_view name, sf::Vector2f size) : 
	name{ name },
	size{ size }						
{}

std::vector<std::unique_ptr<Enemy>> Stage::spawn()
{
	return std::vector<std::unique_ptr<Enemy>>();
}

void Stage::setWaveNumber(int newWaveNumber)
{
	waveNumber = newWaveNumber;
}
