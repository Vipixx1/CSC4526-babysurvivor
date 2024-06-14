#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum class MenuState {
	inMainMenu,
	inPlayMenu,
	inSettingsMenu
};

class GameMenu {
private:
	MenuState menuState{ MenuState::inMainMenu };

	sf::Text gameTitle;

	sf::Text playButtonText;
	sf::Text settingsButtonText;
	sf::Text exitButtonText;

	sf::Text resolutionText;
	sf::Text resolution1;
	sf::Text resolution2;
	sf::Text resolution3;
	sf::Text controlsText;

	sf::Text saveFile1;
	sf::Text saveFile2;
	sf::Text saveFile3;

	sf::Font font;

	int currentMainMenuButton{ 0 };

	int currentResolution{ -1 };

	int currentSaveFile{ 0 };

	std::vector<sf::Text> textVector;
	std::vector<sf::Text> currentResVector;
	std::vector<sf::Text> saveFileVector;

	void renderMenu(sf::RenderWindow& gameWindow, int currentMenu);

	void initializeText(sf::Text& text, const std::string& textString, int size, sf::Vector2f position, sf::Color color) const;

	int processMainMenuEvent(sf::Event event, sf::RenderWindow& gameWindow);
	int processPlayMenuEvent(sf::Event event, sf::RenderWindow& gameWindow);
	int processSettingsMenuEvent(sf::Event event, sf::RenderWindow& gameWindow);

public:
	explicit GameMenu();

	void renderMainMenu(sf::RenderWindow& gameWindow) const;
	void renderPlayMenu(sf::RenderWindow& gameWindow) const;
	void renderSettingMenu(sf::RenderWindow& gameWindow) const;

	int processMenuEvent(sf::Event event, sf::RenderWindow& gameWindow);

	MenuState getMenuState() const;
};