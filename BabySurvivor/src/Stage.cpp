#include "Stage.h"

Stage::Stage(std::string_view name, sf::Vector2f size) : 
	name{ name },
	size{ size }						
{}

std::vector<std::unique_ptr<Enemy>> Stage::spawn() {
	for (int i = 0; i < 10; i++) {
		auto newEnemy = std::make_unique<Enemy>(EnemyType::Broccoli, waveNumber);
	}
}

void Stage::setWaveNumber(int newWaveNumber)
{
	waveNumber = newWaveNumber;
}
