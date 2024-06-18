#include "SoundManager.h"

SoundManager::SoundManager()
{
	sf::SoundBuffer buffer1;
	sf::SoundBuffer buffer2;
	sf::SoundBuffer buffer3;
	sf::SoundBuffer buffer4;
	sf::SoundBuffer buffer5;

	buffer1.loadFromFile("resources/audio/playerShoot.wav");
	buffer2.loadFromFile("resources/audio/heal.wav");
	buffer3.loadFromFile("resources/audio/money.wav");
	buffer4.loadFromFile("resources/audio/xp.wav");
	buffer5.loadFromFile("resources/audio/sujet_micro-projet_CSC4526_2023_2024.wav");

	soundBuffers.push_back(buffer1);
	soundBuffers.push_back(buffer2);
	soundBuffers.push_back(buffer3);
	soundBuffers.push_back(buffer4);
	soundBuffers.push_back(buffer5);

	sf::Sound sound1;
	sf::Sound sound2;
	sf::Sound sound3;
	sf::Sound sound4;
	sf::Sound sound5;

	sounds.push_back(sound1);
	sounds.push_back(sound2);
	sounds.push_back(sound3);
	sounds.push_back(sound4);
	sounds.push_back(sound5);
}

void SoundManager::playSound(int index)
{
	sounds[index].setVolume(volumeLevel);
	sounds[index].setBuffer(soundBuffers[index]);
	sounds[index].play();
}

void SoundManager::changeVolume(int newVolumeLevel)
{
	volumeLevel = static_cast<float>(newVolumeLevel * 20);
}