#include "SoundManager.h"

void SoundManager::loadSoundInBuffer(const std::string& filePath)
{
	soundBuffer.loadFromFile(filePath);
}

void SoundManager::playSound(const std::string& filePath)
{
	loadSoundInBuffer(filePath);
	sound.setBuffer(soundBuffer);
	sound.play();
}

void SoundManager::changeVolume(int newVolumeLevel)
{
	sound.setVolume(static_cast<float>(newVolumeLevel * 20));
}