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

	sf::Text resolutionText;
	sf::Text resolution1;
	sf::Text resolution2;
	sf::Text resolution3;
	
	sf::Text volumeText;
	sf::Text volumeLevel0;
	sf::Text volumeLevel1;
	sf::Text volumeLevel2;
	sf::Text volumeLevel3;
	sf::Text volumeLevel4;
	sf::Text volumeLevel5;

	sf::Text saveFile1;
	sf::Text saveFile2;
	sf::Text saveFile3;

	initializeText(playButtonText, "Play", 30, sf::Vector2f(380.f, 300.f), sf::Color::Yellow);
	initializeText(settingsButtonText, "Settings", 30, sf::Vector2f(380.f, 355.f), sf::Color::White);
	initializeText(exitButtonText, "Exit", 30, sf::Vector2f(380.f, 410.f), sf::Color::White);

	initializeText(gameTitle, "Baby Survivor", 75, sf::Vector2f(300.f, 100.f), sf::Color(122, 103, 6));


	initializeText(resolutionText, "Resolution:", 30, sf::Vector2f(380.f, 200.f), sf::Color::Yellow);
	initializeText(resolution1, "1920x1080", 20, sf::Vector2f(550.f, 210.f), sf::Color::White);
	initializeText(resolution2, "1280x800", 20, sf::Vector2f(660.f, 210.f), sf::Color::White);
	initializeText(resolution3, "1024x768", 20, sf::Vector2f(760.f, 210.f), sf::Color::White);
	initializeText(controlsText, "Controls:\nZQSD to move\nAutofire at the mouse\n\nPress esc to get back to the previous menu"
		, 30, sf::Vector2f(380.f, 300.f), sf::Color::White);

	initializeText(saveFile1, "Save file 1", 30, sf::Vector2f(380.f, 200.f), sf::Color::Yellow);
	initializeText(saveFile2, "Save file 2", 30, sf::Vector2f(380.f, 255.f), sf::Color::White);
	initializeText(saveFile3, "Save file 3", 30, sf::Vector2f(380.f, 310.f), sf::Color::White);

	initializeText(volumeText, "Volume: ", 30, sf::Vector2f(380.f, 260.f), sf::Color::White);

	initializeText(volumeLevel0, "0", 20, sf::Vector2f(500.f, 270.f), sf::Color::White);
	initializeText(volumeLevel1, "1", 20, sf::Vector2f(520.f, 270.f), sf::Color::White);
	initializeText(volumeLevel2, "2", 20, sf::Vector2f(530.f, 270.f), sf::Color::White);
	initializeText(volumeLevel3, "3", 20, sf::Vector2f(550.f, 270.f), sf::Color::White);
	initializeText(volumeLevel4, "4", 20, sf::Vector2f(570.f, 270.f), sf::Color::White);
	initializeText(volumeLevel5, "5", 20, sf::Vector2f(590.f, 270.f), sf::Color::White);

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

	volumeLevelVector.push_back(volumeLevel0);
	volumeLevelVector.push_back(volumeLevel1);
	volumeLevelVector.push_back(volumeLevel2);
	volumeLevelVector.push_back(volumeLevel3);
	volumeLevelVector.push_back(volumeLevel4);
	volumeLevelVector.push_back(volumeLevel5);

	settingOptions.push_back(resolutionText);
	settingOptions.push_back(volumeText);
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

	for (const auto& settingOption : settingOptions)
	{
		gameWindow.draw(settingOption);
	}
	
	for (const auto& res : currentResVector)
	{
		gameWindow.draw(res);
	}

	for (const auto& volume : volumeLevelVector)
	{
		gameWindow.draw(volume);
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
	if (event.key.code == sf::Keyboard::Enter && !insideOption)
	{
		if (currentSettingButton == 0)
		{
			settingOptions[0].setFillColor(sf::Color::White);
			currentResVector[currentResolution].setFillColor(sf::Color::Yellow);
		}

		if (currentSettingButton == 1)
		{
			settingOptions[1].setFillColor(sf::Color::White);
			volumeLevelVector[currentVolumeLevel].setFillColor(sf::Color::Yellow);
		}
		
		insideOption = true;

		return -1;
	}

	if (event.key.code == sf::Keyboard::Enter && insideOption)
	{
		if (currentSettingButton == 0)
		{
			return currentResolution + 3;
		}
		else
		{
			return currentVolumeLevel + 7;
		}
	}

	if (event.key.code == sf::Keyboard::Right && insideOption)
	{
		if (currentSettingButton == 0 && currentResolution < 2)
		{
			currentResolution++;

			currentResVector[currentResolution - 1].setFillColor(sf::Color::White);
			currentResVector[currentResolution].setFillColor(sf::Color::Yellow);
		}

		if (currentSettingButton == 1 && currentVolumeLevel < 5)
		{
			currentVolumeLevel++;

			volumeLevelVector[currentVolumeLevel - 1].setFillColor(sf::Color::White);
			volumeLevelVector[currentVolumeLevel].setFillColor(sf::Color::Yellow);
		}
		
	}

	if (event.key.code == sf::Keyboard::Left && insideOption)
	{
		if (currentSettingButton == 0 && currentResolution > 0)
		{
			currentResolution--;

			currentResVector[currentResolution + 1].setFillColor(sf::Color::White);
			currentResVector[currentResolution].setFillColor(sf::Color::Yellow);
		}

		if (currentSettingButton == 1 && currentVolumeLevel > 0)
		{
			currentVolumeLevel--;

			volumeLevelVector[currentVolumeLevel + 1].setFillColor(sf::Color::White);
			volumeLevelVector[currentVolumeLevel].setFillColor(sf::Color::Yellow);
		}
		
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		if (!insideOption)
		{
			renderMenu(gameWindow, 3);
			return 6;
		}

		if (insideOption)
		{
			if (currentSettingButton == 0)
			{
				currentResVector[currentResolution].setFillColor(sf::Color::White);
			}
			if (currentSettingButton == 1)
			{
				volumeLevelVector[currentVolumeLevel].setFillColor(sf::Color::White);
			}

			insideOption = false;
			settingOptions[currentSettingButton].setFillColor(sf::Color::Yellow);
		}
		
	}

	if (event.key.code == sf::Keyboard::Down && currentSettingButton < 1)
	{
		currentSettingButton++;

		settingOptions[currentSettingButton - 1].setFillColor(sf::Color::White);
		settingOptions[currentSettingButton].setFillColor(sf::Color::Yellow);
	}

	if (event.key.code == sf::Keyboard::Up && currentSettingButton > 0)
	{
		currentSettingButton--;

		settingOptions[currentSettingButton + 1].setFillColor(sf::Color::White);
		settingOptions[currentSettingButton].setFillColor(sf::Color::Yellow);
	}

	return -1;
}

MenuState GameMenu::getMenuState() const
{
	return menuState;
}