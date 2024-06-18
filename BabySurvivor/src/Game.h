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
	sf::RenderWindow gameWindow;
	sf::View view;

	static const sf::Time TimePerFrame;
	sf::Time statsUpdateTime;
	std::size_t numFrames{ 0 };
	sf::Text statsText;
	sf::Font font;
	
	GameState gameState;
	GameMenu gameMenu;

	//std::shared_ptr<Player> player;
	Stage stage{ "stage_1" };

	std::vector<std::unique_ptr<Collectible>> collectibles;

	void processGeneralEvent(sf::Event event);
	void processMenuEvent();
	void processInGameEvent();
	void updateStatsText(sf::Time elapsedTime);

public:
	Game();
	void run();
	
	// Functions needed for testing purposes
	std::unique_ptr<Player> loadPlayer(int saveFileNumber);
	std::shared_ptr<Player> getGamePlayer();
};
