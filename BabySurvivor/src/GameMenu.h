#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

enum class MenuState {
	inMainMenu,
	inPlayMenu,
	inSettingsMenu,
	inUpgradeMenu,
	inGameOverMenu,
	inWinMenu
};

class GameMenu {
private:
	MenuState menuState{ MenuState::inMainMenu };

	sf::Text gameTitle;
	sf::Text controlsText;
	sf::Font font;
	sf::Text moneyText;
	sf::Text volumeText;
	sf::Text gameOverText;
	sf::Text winText;

	bool insideOption{ false };

	int currentMainMenuButton{ 0 };
	int currentResolution{ 0 };
	int currentSaveFile{ 0 };
	int currentVolumeLevel{ 0 };
	int currentUpgrade{ 0 };

	int playerMoney{ 0 };

	std::array<int, 4> upgradeLevel{ 0, 0, 0, 0 };
	std::array<int, 20> upgradeRequierment{ 50, 150, 300, 500, 1000,
										   50, 150, 300, 500, 1000,
										   50, 150, 300, 500, 1000,
										   50, 150, 300, 500, 1000 };

	std::vector<sf::Text> textVector;
	std::vector<sf::Text> saveFileVector;
	std::vector<sf::Text> volumeLevelVector;
	std::vector<sf::Text> upgradeOptions;

	void renderMenu(sf::RenderWindow& gameWindow, int currentMenu);

	void initializeText(sf::Text& text, const std::string& textString, int size, sf::Vector2f position, sf::Color color) const;
	

	int processMainMenuEvent(sf::Event event, sf::RenderWindow& gameWindow);
	int processPlayMenuEvent(sf::Event event, sf::RenderWindow& gameWindow);
	int processSettingsMenuEvent(sf::Event event, sf::RenderWindow& gameWindow);
	int processUpgradeMenuEvent(sf::Event event, sf::RenderWindow& gameWindow);
	int processEndMenuEvent(sf::Event event, sf::RenderWindow& gameWindow) const;

public:
	explicit GameMenu();

	void renderMainMenu(sf::RenderWindow& gameWindow) const;
	void renderPlayMenu(sf::RenderWindow& gameWindow) const;
	void renderUpgradeMenu(sf::RenderWindow& gameWindow);
	void renderSettingMenu(sf::RenderWindow& gameWindow) const;
	void renderGameOverMenu(sf::RenderWindow& gameWindow);
	void renderWinMenu(sf::RenderWindow& gameWindow);

	int processMenuEvent(sf::Event event, sf::RenderWindow& gameWindow);

	MenuState getMenuState() const;

	// This function is public for testing purposes
	void updateUpgradeMenu();
	void updateJson(int changedUpgrade);

	// These functions are added for testing purposes
	void setCurrentSaveFile(int newSaveFileIndex);
	void setUpgradeLevel(int upgradeIndex, int newLevel);
};