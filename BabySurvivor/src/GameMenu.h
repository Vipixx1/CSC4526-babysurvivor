#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class GameMenu {
private:
	sf::Text gameTitle;

	sf::Text playButtonText;
	sf::Text settingsButtonText;
	sf::Text exitButtonText;

	sf::Vector2f playButtonCoords{ 480.f, 300.f };
	sf::Vector2f settingButtonCoords{ 480.f, 355.f };
	sf::Vector2f exitButtonCoords{ 480.f, 410.f };

	sf::Font font;

	int currentButton{ 0 };

	std::vector<sf::Text> textVector;
	std::vector<sf::RectangleShape> buttonVector;

	void renderMenu(sf::RenderWindow& gameWindow, int currentMenu);

public:
	explicit GameMenu();

	void renderMainMenu(sf::RenderWindow& gameWindow) const;
	void renderPlayMenu(sf::RenderWindow& gameWindow) const;
	void renderSettingMenu(sf::RenderWindow& gameWindow) const;

	int processMenuEvent(sf::Event event, sf::RenderWindow& gameWindow);
};