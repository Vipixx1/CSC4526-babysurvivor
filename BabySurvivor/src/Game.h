#pragma once 
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Stage.h"
#include "GameMenu.h"
#include "SoundManager.h"

int startGame();

enum class GameState {
	inGame,
	inMenu,
};

class Game {
private:
	std::vector<std::tuple<int, int>> resolutionVector{ std::make_tuple(1920, 1080),
														std::make_tuple(1280, 800),
														std::make_tuple(1024, 768) };

	int currentResolution{ 0 };

	sf::RenderWindow gameWindow;
	sf::View view;

	static const sf::Time TimePerFrame;
	sf::Time statsUpdateTime;
	std::size_t numFrames{ 0 };
	sf::Text statsText;
	sf::Font font;
	
	GameState gameState;
	GameMenu gameMenu;

	SoundManager soundManager;

	std::shared_ptr<Player> player;
	Stage stage{ "stage_1" };

	std::vector<std::unique_ptr<Collectible>> collectibles;

	void changeResolution(int newResolutionIndex);

	void processGeneralEvent(sf::Event event);
	void processMenuEvent();
	void processInGameEvent();

	void loadPlayer(int saveFileNumber);

	void updateStatsText(sf::Time elapsedTime);

public:
	Game();
	void run();
	
};
