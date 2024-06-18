#pragma once

#include <SFML/Audio.hpp>
#include <vector>

class SoundManager {
private:
	float volumeLevel{ 100.f };

	std::vector<sf::SoundBuffer> soundBuffers;
	std::vector<sf::Sound> sounds;

public:
	SoundManager();

	void playSound(int soundIndex);
	void changeVolume(int newVolumeLevel);
};