#include "GameMenu.h"

GameMenu::GameMenu() 
{
	font.loadFromFile("resources/Sansation.ttf");

	playButtonText.setPosition(playButtonCoords);
	settingsButtonText.setPosition(settingButtonCoords);
	exitButtonText.setPosition(exitButtonCoords);

	playButtonText.setFont(font);
	playButtonText.setCharacterSize(30);
	playButtonText.setString("Play");
	playButtonText.setFillColor(sf::Color::Yellow);

	settingsButtonText.setFont(font);
	settingsButtonText.setCharacterSize(30);
	settingsButtonText.setString("Settings");

	exitButtonText.setFont(font);
	exitButtonText.setCharacterSize(30);
	exitButtonText.setString("Exit");

	gameTitle.setFont(font);
	gameTitle.setCharacterSize(50);
	gameTitle.setString("Baby Survivor");
	gameTitle.setFillColor(sf::Color(122, 103, 6));

	textVector.push_back(playButtonText);
	textVector.push_back(settingsButtonText);
	textVector.push_back(exitButtonText);
}

void GameMenu::renderMenu(sf::RenderWindow& gameWindow, int currentMenu)
{
	switch (currentMenu)
	{
	case 0:
		renderPlayMenu(gameWindow);
		break;

	case 1:
		renderSettingMenu(gameWindow);
		break;

	case 2:
		gameWindow.close();
		break;

	default:
		break;
	}

}

void GameMenu::renderMainMenu(sf::RenderWindow& gameWindow) const
{
	gameWindow.clear(sf::Color::Cyan);

	gameWindow.draw(gameTitle);

	for (const auto& text : textVector)
	{
		gameWindow.draw(text);
	}

	gameWindow.display();
}

void GameMenu::renderPlayMenu(sf::RenderWindow& gameWindow) const
{
	gameWindow.clear(sf::Color::Blue);

	gameWindow.display();
}

void GameMenu::renderSettingMenu(sf::RenderWindow& gameWindow) const
{
	gameWindow.clear(sf::Color(128, 128, 128));

	gameWindow.display();
}

int GameMenu::processMenuEvent(sf::Event event, sf::RenderWindow& gameWindow)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Down && currentButton < 2)
		{
			currentButton++;

			textVector[currentButton - 1].setFillColor(sf::Color::White);
			textVector[currentButton].setFillColor(sf::Color::Yellow);

			return -1;
		}

		if (event.key.code == sf::Keyboard::Up && currentButton > 0)
		{
			currentButton--;

			textVector[currentButton + 1].setFillColor(sf::Color::White);
			textVector[currentButton].setFillColor(sf::Color::Yellow);

			return -1;
		}

		if (event.key.code == sf::Keyboard::Enter)
		{
			renderMenu(gameWindow, currentButton);
			return currentButton;
		}
	}

	else return -1;
}