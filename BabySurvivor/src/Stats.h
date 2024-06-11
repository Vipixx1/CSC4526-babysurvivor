#pragma once

class Stats {
private:
	int baseHealth;
	int currentHealt;
	int baseDamge;
	int damageMultiplier;
	float baseSpeed;

public:
	Stats();
	float getSpeed();
};