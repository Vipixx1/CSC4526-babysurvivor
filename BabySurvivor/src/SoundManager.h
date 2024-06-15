#pragma once

#include <SFML/Audio.hpp>

class SoundManager {
private:
	sf::Sound sound;
	sf::SoundBuffer soundBuffer;

	void loadSoundInBuffer(const std::string& filePath);

public:
	SoundManager() = default;

	void playSound(const std::string& filePath);
	void changeVolume(int newVolumeLevel);
};