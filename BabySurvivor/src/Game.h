#pragma once 
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Stage.h"
#include "GameMenu.h"

int startGame();

enum class GameState {
	inGame,
	inMenu,
};

class Game {
private:
	sf::RenderWindow gameWindow;
	sf::View view;

	static const sf::Time TimePerFrame;
	sf::Time statsUpdateTime;
	std::size_t numFrames{ 0 };

	sf::Text statsText;
	sf::Font font;
	
	GameState gameState;
	GameMenu gameMenu;

	bool gameOver{ false };

	Stage stage{ "stage_1" };

	void processGeneralEvent(sf::Event event);
	void processMenuEvent();
	void processInGameEvent();
	void updateStatsText(sf::Time elapsedTime);

public:
	Game();
	void run();

	std::unique_ptr<Player> loadPlayer(int saveFileNumber);
	
	/* Functions needed for testing purposes */
};
