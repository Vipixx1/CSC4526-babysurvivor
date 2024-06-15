#include "GameMenu.h"
#include <iostream>

void GameMenu::initializeText(sf::Text& text, const std::string& textString, int size, sf::Vector2f position, sf::Color color) const
{
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setString(textString);
	text.setPosition(position);
}

GameMenu::GameMenu() 
{
	font.loadFromFile("resources/Sansation.ttf");

	sf::Text playButtonText;
	sf::Text settingsButtonText;
	sf::Text exitButtonText;

	sf::Text resolution1;
	sf::Text resolution2;
	sf::Text resolution3;

	sf::Text saveFile1;
	sf::Text saveFile2;
	sf::Text saveFile3;

	initializeText(playButtonText, "Play", 30, sf::Vector2f(380.f, 300.f), sf::Color::Yellow);
	initializeText(settingsButtonText, "Settings", 30, sf::Vector2f(380.f, 355.f), sf::Color::White);
	initializeText(exitButtonText, "Exit", 30, sf::Vector2f(380.f, 410.f), sf::Color::White);

	initializeText(gameTitle, "Baby Survivor", 75, sf::Vector2f(300.f, 100.f), sf::Color(122, 103, 6));

	
	initializeText(resolutionText, "Resolution :", 30, sf::Vector2f(380.f, 200.f), sf::Color::Yellow);
	initializeText(resolution1, "1920x1080", 20, sf::Vector2f(550.f, 210.f), sf::Color::White);
	initializeText(resolution2, "1280x800", 20, sf::Vector2f(660.f, 210.f), sf::Color::White);
	initializeText(resolution3, "1024x768", 20, sf::Vector2f(760.f, 210.f), sf::Color::White);
	initializeText(controlsText, "Controls:\nZQSD to move\nAutofire at the mouse\n\nPress esc to get back to the previous menu"
			, 30, sf::Vector2f(380.f, 245.f), sf::Color::White);

	initializeText(saveFile1, "Save file 1", 30, sf::Vector2f(380.f, 200.f), sf::Color::Yellow);
	initializeText(saveFile2, "Save file 2", 30, sf::Vector2f(380.f, 255.f), sf::Color::White);
	initializeText(saveFile3, "Save file 3", 30, sf::Vector2f(380.f, 310.f), sf::Color::White);


	// Add the texts to the vector containing all texts
	textVector.push_back(playButtonText);
	textVector.push_back(settingsButtonText);
	textVector.push_back(exitButtonText);

	currentResVector.push_back(resolution1);
	currentResVector.push_back(resolution2);
	currentResVector.push_back(resolution3);

	saveFileVector.push_back(saveFile1);
	saveFileVector.push_back(saveFile2);
	saveFileVector.push_back(saveFile3);
}

void GameMenu::renderMenu(sf::RenderWindow& gameWindow, int currentMenu)
{
	switch (currentMenu)
	{
	case 0:
		menuState = MenuState::inPlayMenu;
		renderPlayMenu(gameWindow);
		break;

	case 1:
		menuState = MenuState::inSettingsMenu;
		renderSettingMenu(gameWindow);
		break;

	case 2:
		gameWindow.close();
		break;

	case 3:
		menuState = MenuState::inMainMenu;
		renderMainMenu(gameWindow);
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

	for (const auto& save : saveFileVector)
	{
		gameWindow.draw(save);
	}

	gameWindow.display();
}

void GameMenu::renderSettingMenu(sf::RenderWindow& gameWindow) const
{
	gameWindow.clear(sf::Color(128, 128, 128));

	gameWindow.draw(resolutionText);
	
	for (const auto& res : currentResVector)
	{
		gameWindow.draw(res);
	}

	gameWindow.draw(controlsText);

	gameWindow.display();
}

int GameMenu::processMenuEvent(sf::Event event, sf::RenderWindow& gameWindow)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (menuState == MenuState::inMainMenu) {
			return processMainMenuEvent(event, gameWindow);
		}
		
		if (menuState == MenuState::inSettingsMenu)
		{
			return  processSettingsMenuEvent(event, gameWindow);
		}

		if (menuState == MenuState::inPlayMenu)
		{
			return processPlayMenuEvent(event, gameWindow);
		}
	}

	else return -1;
}

int GameMenu::processMainMenuEvent(sf::Event event, sf::RenderWindow& gameWindow)
{
	if (event.key.code == sf::Keyboard::Down && currentMainMenuButton < 2)
	{
		currentMainMenuButton++;

		textVector[currentMainMenuButton - 1].setFillColor(sf::Color::White);
		textVector[currentMainMenuButton].setFillColor(sf::Color::Yellow);

		return -1;
	}

	if (event.key.code == sf::Keyboard::Up && currentMainMenuButton > 0)
	{
		currentMainMenuButton--;

		textVector[currentMainMenuButton + 1].setFillColor(sf::Color::White);
		textVector[currentMainMenuButton].setFillColor(sf::Color::Yellow);

		return -1;
	}

	if (event.key.code == sf::Keyboard::Enter)
	{
		renderMenu(gameWindow, currentMainMenuButton);
		return -1;
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		gameWindow.close();
		return -1;
	}
}

int GameMenu::processPlayMenuEvent(sf::Event event, sf::RenderWindow& gameWindow)
{
	if (event.key.code == sf::Keyboard::Enter)
	{
		// The return value of the save file to use
		return currentSaveFile;
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		renderMenu(gameWindow, 3);
		return 6;
	}

	if (event.key.code == sf::Keyboard::Down && currentSaveFile < 2)
	{
		currentSaveFile++;

		saveFileVector[currentSaveFile - 1].setFillColor(sf::Color::White);
		saveFileVector[currentSaveFile].setFillColor(sf::Color::Yellow);
	}

	if (event.key.code == sf::Keyboard::Up && currentSaveFile > 0)
	{
		currentSaveFile--;

		saveFileVector[currentSaveFile + 1].setFillColor(sf::Color::White);
		saveFileVector[currentSaveFile].setFillColor(sf::Color::Yellow);
	}
	
	return -1;
}

int GameMenu::processSettingsMenuEvent(sf::Event event, sf::RenderWindow& gameWindow)
{
	if (event.key.code == sf::Keyboard::Enter && currentResolution < 0)
	{
		resolutionText.setFillColor(sf::Color::White);
		currentResVector[0].setFillColor(sf::Color::Yellow);

		currentResolution = 0;

		return -1;
	}

	if (event.key.code == sf::Keyboard::Enter && currentResolution >= 0)
	{
		return currentResolution + 3;
	}

	if (event.key.code == sf::Keyboard::Right && currentResolution < 2 && currentResolution >= 0)
	{
		currentResolution++;

		std::cout << currentResolution << std::endl;

		currentResVector[currentResolution - 1].setFillColor(sf::Color::White);
		currentResVector[currentResolution].setFillColor(sf::Color::Yellow);
	}

	if (event.key.code == sf::Keyboard::Left && currentResolution > 0)
	{
		currentResolution--;

		std::cout << currentResolution << std::endl;

		currentResVector[currentResolution + 1].setFillColor(sf::Color::White);
		currentResVector[currentResolution].setFillColor(sf::Color::Yellow);
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		renderMenu(gameWindow, 3);
		return 6;
	}

	return -1;
}

MenuState GameMenu::getMenuState() const
{
	return menuState;
}