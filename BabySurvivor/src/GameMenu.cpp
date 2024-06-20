#include "GameMenu.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

void GameMenu::initializeText(sf::Text& text, const std::string& textString, int size, sf::Vector2f position, sf::Color color) const
{
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setString(textString);
	text.setPosition(position);
}

void GameMenu::updateUpgradeMenu()
{
	std::string player = std::format("player{}", currentSaveFile + 1);

	std::ifstream f("resources/Entity.json");
	json allData = json::parse(f);
	f.close();

	json playerData = allData.at(player);

	std::array < std::string, 4> upgradeNames{ "Damage: ", "Damage multiplier: ", "Health: ", "Speed: " };
	
	upgradeLevel[0] = playerData.at("damageUpgrade");
	upgradeLevel[1] = playerData.at("damageMultiplierUpgrade");
	upgradeLevel[2] = playerData.at("healthUpgrade");
	upgradeLevel[3] = playerData.at("speedUpgrade");

	playerMoney = playerData.at("money");

	moneyText.setString(std::format("Money: {}", playerMoney));
	
	for (int i = 1; i < 5; i++) {
		upgradeOptions[i].setString(std::format("{}{}/5", upgradeNames[i - 1], upgradeLevel[i - 1]));
	}
}

GameMenu::GameMenu()
{
	font.loadFromFile("resources/Sansation.ttf");

	sf::Text playButtonText;
	sf::Text settingsButtonText;
	sf::Text exitButtonText;
	
	sf::Text volumeLevel0;
	sf::Text volumeLevel1;
	sf::Text volumeLevel2;
	sf::Text volumeLevel3;
	sf::Text volumeLevel4;
	sf::Text volumeLevel5;

	sf::Text saveFile1;
	sf::Text saveFile2;
	sf::Text saveFile3;

	sf::Text play;
	sf::Text baseDamage;
	sf::Text damageMultiplier;
	sf::Text baseHealth;
	sf::Text baseSpeed;

	initializeText(playButtonText, "Play", 30, sf::Vector2f(380.f, 300.f), sf::Color::Yellow);
	initializeText(settingsButtonText, "Settings", 30, sf::Vector2f(380.f, 355.f), sf::Color::White);
	initializeText(exitButtonText, "Exit", 30, sf::Vector2f(380.f, 410.f), sf::Color::White);

	initializeText(gameTitle, "Baby Survivor", 75, sf::Vector2f(300.f, 100.f), sf::Color(122, 103, 6));

	initializeText(controlsText, "Controls:\nZQSD to move\nAutofire at the mouse\n\nPress esc to get back to the previous menu"
		, 30, sf::Vector2f(380.f, 300.f), sf::Color::White);

	initializeText(saveFile1, "Save file 1", 30, sf::Vector2f(380.f, 200.f), sf::Color::Yellow);
	initializeText(saveFile2, "Save file 2", 30, sf::Vector2f(380.f, 255.f), sf::Color::White);
	initializeText(saveFile3, "Save file 3 (cheat)", 30, sf::Vector2f(380.f, 310.f), sf::Color::White);

	initializeText(volumeText, "Volume: ", 30, sf::Vector2f(380.f, 260.f), sf::Color::Yellow);

	initializeText(volumeLevel0, "0", 20, sf::Vector2f(500.f, 270.f), sf::Color::White);
	initializeText(volumeLevel1, "1", 20, sf::Vector2f(520.f, 270.f), sf::Color::White);
	initializeText(volumeLevel2, "2", 20, sf::Vector2f(530.f, 270.f), sf::Color::White);
	initializeText(volumeLevel3, "3", 20, sf::Vector2f(550.f, 270.f), sf::Color::White);
	initializeText(volumeLevel4, "4", 20, sf::Vector2f(570.f, 270.f), sf::Color::White);
	initializeText(volumeLevel5, "5", 20, sf::Vector2f(590.f, 270.f), sf::Color::White);

	initializeText(play, "Play", 30, sf::Vector2f(380.f, 200.f), sf::Color::Yellow);
	initializeText(baseDamage, "Damage", 30, sf::Vector2f(380.f, 255.f), sf::Color::White);
	initializeText(damageMultiplier, "Damage Multiplier", 30, sf::Vector2f(380.f, 310.f), sf::Color::White);
	initializeText(baseHealth, "Health", 30, sf::Vector2f(380.f, 365.f), sf::Color::White);
	initializeText(baseSpeed, "Speed", 30, sf::Vector2f(380.f, 420.f), sf::Color::White);

	initializeText(moneyText, "Money: ", 30, sf::Vector2f(700.f, 500.f), sf::Color(255, 215, 0));

	initializeText(gameOverText, "Game over !", 75, sf::Vector2f(380.f, 200.f), sf::Color::Red);
	initializeText(winText, "You win !", 75, sf::Vector2f(380.f, 200.f), sf::Color(255, 215, 0));

	// Add the texts to the vector containing all texts
	textVector.push_back(playButtonText);
	textVector.push_back(settingsButtonText);
	textVector.push_back(exitButtonText);

	saveFileVector.push_back(saveFile1);
	saveFileVector.push_back(saveFile2);
	saveFileVector.push_back(saveFile3);

	volumeLevelVector.push_back(volumeLevel0);
	volumeLevelVector.push_back(volumeLevel1);
	volumeLevelVector.push_back(volumeLevel2);
	volumeLevelVector.push_back(volumeLevel3);
	volumeLevelVector.push_back(volumeLevel4);
	volumeLevelVector.push_back(volumeLevel5);

	upgradeOptions.push_back(play);
	upgradeOptions.push_back(baseDamage);
	upgradeOptions.push_back(damageMultiplier);
	upgradeOptions.push_back(baseHealth);
	upgradeOptions.push_back(baseSpeed);
}

void GameMenu::renderMenu(sf::RenderWindow& gameWindow, int currentMenu)
{
	switch (currentMenu)
	{
		case 0:
		{
			menuState = MenuState::inPlayMenu;
			renderPlayMenu(gameWindow);
			break;
		}
		
		case 1:
		{
			menuState = MenuState::inSettingsMenu;
			renderSettingMenu(gameWindow);
			break;
		}

		case 2:
		{
			gameWindow.close();
			break;
		}

		case 3:
		{
			menuState = MenuState::inMainMenu;
			renderMainMenu(gameWindow);
			break;
		}

		case 4:
		{
			menuState = MenuState::inUpgradeMenu;
			renderUpgradeMenu(gameWindow);
			break;
		}
	
		case 5:
		{
			menuState = MenuState::inGameOverMenu;
			renderGameOverMenu(gameWindow);
			break;
		}

		case 6:
		{
			menuState = MenuState::inWinMenu;
			renderWinMenu(gameWindow);
			break;
		}

		default:
		{
			break;
		}
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

	gameWindow.draw(volumeText);

	for (const auto& volume : volumeLevelVector)
	{
		gameWindow.draw(volume);
	}

	gameWindow.draw(controlsText);

	gameWindow.display();
}

void GameMenu::renderUpgradeMenu(sf::RenderWindow& gameWindow)
{
	updateUpgradeMenu();

	gameWindow.clear(sf::Color(185, 119, 201));

	gameWindow.draw(moneyText);
	
	for (const auto& upgrade : upgradeOptions)
	{
		gameWindow.draw(upgrade);
	}

	gameWindow.display();
}

void GameMenu::renderGameOverMenu(sf::RenderWindow& gameWindow)
{
	menuState = MenuState::inGameOverMenu;
	gameWindow.clear(sf::Color(250, 84, 72));
	gameWindow.draw(gameOverText);
	gameWindow.display();
}

void GameMenu::renderWinMenu(sf::RenderWindow& gameWindow)
{
	menuState = MenuState::inWinMenu;
	gameWindow.clear(sf::Color(59, 179, 50));
	gameWindow.draw(winText);
	gameWindow.display();
}

int GameMenu::processMenuEvent(sf::Event event, sf::RenderWindow& gameWindow)
{
	if (event.type == sf::Event::KeyPressed)
	{
		using enum MenuState;
		if (menuState == inMainMenu) {
			return processMainMenuEvent(event, gameWindow);
		}
		
		if (menuState == inSettingsMenu)
		{
			return  processSettingsMenuEvent(event, gameWindow);
		}

		if (menuState == inPlayMenu)
		{
			return processPlayMenuEvent(event, gameWindow);
		}

		if (menuState == inUpgradeMenu)
		{
			return processUpgradeMenuEvent(event, gameWindow);
		}

		if (menuState == inGameOverMenu || menuState == inWinMenu) 
		{
			return processEndMenuEvent(event, gameWindow);
		}
	}
	return -1;
}

int GameMenu::processMainMenuEvent(sf::Event event, sf::RenderWindow& gameWindow)
{
	if (event.key.code == sf::Keyboard::Down && currentMainMenuButton < 2)
	{
		currentMainMenuButton++;

		textVector[currentMainMenuButton - 1].setFillColor(sf::Color::White);
		textVector[currentMainMenuButton].setFillColor(sf::Color::Yellow);
	}

	if (event.key.code == sf::Keyboard::Up && currentMainMenuButton > 0)
	{
		currentMainMenuButton--;

		textVector[currentMainMenuButton + 1].setFillColor(sf::Color::White);
		textVector[currentMainMenuButton].setFillColor(sf::Color::Yellow);
	}

	if (event.key.code == sf::Keyboard::Enter)
	{
		renderMenu(gameWindow, currentMainMenuButton);
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		gameWindow.close();
	}
	return -1;
}

int GameMenu::processPlayMenuEvent(sf::Event event, sf::RenderWindow& gameWindow)
{
	if (event.key.code == sf::Keyboard::Enter)
	{
		renderMenu(gameWindow, 4);
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		renderMenu(gameWindow, 3);
		return 9;
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
		volumeText.setFillColor(sf::Color::White);
		volumeLevelVector[currentVolumeLevel].setFillColor(sf::Color::Yellow);
		insideOption = true;
	}

	if (event.key.code == sf::Keyboard::Enter && insideOption)
	{
			return currentVolumeLevel + 3;
	}

	if (event.key.code == sf::Keyboard::Right && insideOption && currentVolumeLevel < 5)
	{
		currentVolumeLevel++;

		volumeLevelVector[currentVolumeLevel - 1].setFillColor(sf::Color::White);
		volumeLevelVector[currentVolumeLevel].setFillColor(sf::Color::Yellow);		
	}

	if (event.key.code == sf::Keyboard::Left && insideOption && currentVolumeLevel > 0)
	{
		currentVolumeLevel--;

		volumeLevelVector[currentVolumeLevel + 1].setFillColor(sf::Color::White);
		volumeLevelVector[currentVolumeLevel].setFillColor(sf::Color::Yellow);	
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		if (!insideOption)
		{
			renderMenu(gameWindow, 3);
			return 9;
		}

		if (insideOption)
		{
			volumeLevelVector[currentVolumeLevel].setFillColor(sf::Color::White);
			insideOption = false;
			volumeText.setFillColor(sf::Color::Yellow);
		}
		
	}
	return -1;
}

int GameMenu::processUpgradeMenuEvent(sf::Event event, sf::RenderWindow& gameWindow)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		renderMenu(gameWindow, 0);
	}

	if (event.key.code == sf::Keyboard::Down && currentUpgrade < 4)
	{
		currentUpgrade++;

		upgradeOptions[currentUpgrade - 1].setFillColor(sf::Color::White);
		upgradeOptions[currentUpgrade].setFillColor(sf::Color::Yellow);
	}

	if (event.key.code == sf::Keyboard::Up && currentUpgrade > 0)
	{
		currentUpgrade--;

		upgradeOptions[currentUpgrade + 1].setFillColor(sf::Color::White);
		upgradeOptions[currentUpgrade].setFillColor(sf::Color::Yellow);
	}

	if (event.key.code == sf::Keyboard::Enter && currentUpgrade > 0 && upgradeLevel[currentUpgrade - 1] < 5)
	{
		int upgradeCost = upgradeRequierment[(currentUpgrade - 1) * 5 + upgradeLevel[currentUpgrade - 1]];

		if (upgradeLevel[currentUpgrade - 1] < 5 && playerMoney >= upgradeCost)
		{
			upgradeLevel[currentUpgrade - 1]++;
			playerMoney -= upgradeCost;
			updateJson(currentUpgrade - 1);
		}
	}

	if (event.key.code == sf::Keyboard::Enter && currentUpgrade == 0)
	{
		return currentSaveFile;
	}

	return -1;
}

int GameMenu::processEndMenuEvent(sf::Event event, sf::RenderWindow& gameWindow)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		renderMenu(gameWindow, 3);
	}

	return -1;
}

void GameMenu::updateJson(int changedUpgrade)
{
	std::string player = std::format("player{}", currentSaveFile + 1);

	std::string upgradeName = "";
	std::string statName = "";

	switch (changedUpgrade) {
		case 0:
			upgradeName = "damageUpgrade";
			statName = "baseDamage";
			break;
		case 1:
			upgradeName = "damageMultiplierUpgrade";
			statName = "damageMultiplier";
			break;
		case 2:
			upgradeName = "healthUpgrade";
			statName = "baseHealth";
			break;
		case 3:
			upgradeName = "speedUpgrade";
			statName = "baseSpeed";
			break;
		default:
			break;
	}

	std::ifstream f("resources/Entity.json");
	json allData = json::parse(f);
	f.close();

	allData[player]["money"] = playerMoney;
	allData[player][statName] = static_cast<float>(allData.at("upgradeValue").at(upgradeName)[upgradeLevel[changedUpgrade] - 1]);

	allData[player][upgradeName] = static_cast<int>(allData.at(player).at(upgradeName)) + 1;

	std::ofstream fout("resources/Entity.json");

	fout << allData.dump(4);

	fout.flush();
	fout.close();
}

MenuState GameMenu::getMenuState() const
{
	return menuState;
}

void GameMenu::setCurrentSaveFile(int newSaveFileIndex)
{
	currentSaveFile = newSaveFileIndex;
}

void GameMenu::setUpgradeLevel(int upgradeIndex, int newLevel)
{
	upgradeLevel[upgradeIndex] = newLevel;
}
