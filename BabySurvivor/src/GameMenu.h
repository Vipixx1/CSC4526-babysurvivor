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
	sf::Text resolutionText;
	sf::Text controlsText;
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