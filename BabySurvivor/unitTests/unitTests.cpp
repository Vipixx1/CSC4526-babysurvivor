#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <fstream>
#include "json.hpp"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"
#include "Stage.h"
#include "Collectible.h"

namespace Baby_Survivor_Test {

	TEST(TestReadPlayer, TestAttributes) {
		//Check all the attributes of the player one
	
		Player playerTest{ "resources/Entity.json", "player1"};
	
		EXPECT_EQ(playerTest.getMaxHealth(), 500);
		EXPECT_EQ(playerTest.getDamage(), 35);
		EXPECT_EQ(playerTest.getDamageMultiplier(), 1.0);
		EXPECT_EQ(playerTest.getSpeed(), 300);
		EXPECT_EQ(playerTest.getShotDelay(), 50);
		EXPECT_EQ(playerTest.getShotSpeed(), 1000);
	}
	
	TEST(TestReadPlayer, TestOtherPlayer) {
		//Check that if we select the second player, its file is selected
	
		
		Game game;
		game.loadPlayer(1);
	
		std::shared_ptr<Player> playerTest = game.getGamePlayer();
	
		EXPECT_EQ(playerTest->getMaxHealth(), 300);
		EXPECT_EQ(playerTest->getDamage(), 20);
		EXPECT_EQ(playerTest->getDamageMultiplier(), 1.0);
		EXPECT_EQ(playerTest->getSpeed(), 350);
		EXPECT_EQ(playerTest->getShotDelay(), 30);
		EXPECT_EQ(playerTest->getShotSpeed(), 1300);
	}
	
	TEST(TestReadEnemy, TestAttributes) {
		//Check all the attributes of several enemies types
	
		// The player is needed to instantiate an enemy as he requiers a target
		Player playerTest{ "resources/Entity.json", "player1" };
	
		Enemy enemyTest1{ "resources/Entity.json", "ghost_v1", playerTest };
		Enemy enemyTest2{ "resources/Entity.json", "tomato_v1", playerTest };
		Enemy enemyTest3{ "resources/Entity.json", "doll_v1", playerTest };

		EXPECT_EQ(enemyTest1.getDamage(), 30);
		EXPECT_EQ(enemyTest2.getDamage(), 40);
		EXPECT_EQ(enemyTest3.getDamage(), 30);
		EXPECT_EQ(enemyTest1.getMaxHealth(), 100);
		EXPECT_EQ(enemyTest2.getMaxHealth(), 130);
		EXPECT_EQ(enemyTest3.getMaxHealth(), 100);
		EXPECT_EQ(enemyTest1.getSpeed(), 150);
		EXPECT_EQ(enemyTest2.getSpeed(), 500);
		EXPECT_EQ(enemyTest3.getSpeed(), 0);
	}

	TEST(TestStage, TestCreation) {
		//Check that the stage is created with the good size
		//Check that the first wave is spawning
	}

	TEST(TestPlayer, TestMovement) {
		//Check that the 4 directions work
		//Check that the player can't be OOB
	}

	TEST(TestStage, TestCollectibleCollection) {
		// Check if a collectible is collected and that it have the right effect on the player

		Stage stage{"stage_1"};
		sf::Vector2f position{ 100.f, 100.f };
		sf::Vector2f position2{ 200.f, 200.f };

		Collectible hp{"resources/Entity.json", "health", CollectibleType::health, 10 };
		hp.setPosition(position);

		Collectible money{ "resources/Entity.json", "money", CollectibleType::money, 1 };
		money.setPosition(position2);

		Collectible xp{ "resources/Entity.json", "experience", CollectibleType::experience, 5 };
		xp.setPosition(position2);

		stage.addCollectible(hp);
		stage.addCollectible(money);
		stage.addCollectible(xp);

		auto playerTest = std::make_shared<Player>("resources/Entity.json", "player1");
		stage.setPlayer(playerTest);

		playerTest->takeDamage(50);

		// We check if the player took the damage
		EXPECT_EQ(playerTest->getCurrentHealth(), playerTest->getMaxHealth() - 50);

		// We move the player to the heal collectible
		playerTest->setPosition(position);

		stage.collectibleCheckCollisions();

		// We check if the player healed for 10 hp
		EXPECT_EQ(playerTest->getCurrentHealth(), playerTest->getMaxHealth() - 40);

		int prevMoney = playerTest->getMoney();
		float prevExp = playerTest->getExperience();

		// We move the player to the second test position
		playerTest->setPosition(position2);

		stage.collectibleCheckCollisions();

		// We check if the player gained the money and experience
		EXPECT_EQ(playerTest->getMoney(), prevMoney + 1);
		EXPECT_EQ(playerTest->getExperience(), prevExp + 5);
	}

	TEST(TestStage, TestProjectileCollision) {
		// We check that ally bullet can damage enemies and that enemy bullets damages the player
		// We also check that friendly bullet can't damage the player and the same for enemy bullets on enemies

		Stage stage{ "stage_1" };
		sf::Vector2f position{ 100.f, 100.f };
		sf::Vector2f position2{ 200.f, 200.f };

		Projectile allyProjectile{ "resources/Entity.json", "projectileAlly", 10, true};
		Projectile enemyProjectile{ "resources/Entity.json", "projectileEnemy", 10, false };
		allyProjectile.setPosition(position);
		allyProjectile.setDirection(sf::Vector2f(0.f, 0.f));
		enemyProjectile.setPosition(position2);
		enemyProjectile.setDirection(sf::Vector2f(0.f, 0.f));
	
		auto playerTest = std::make_shared<Player>("resources/Entity.json", "player1");
		playerTest->setPosition(sf::Vector2f(0.f, 0.f));
		stage.setPlayer(playerTest);

		Enemy enemyTest{ "resources/Entity.json", "ghost_v1", *playerTest };
		enemyTest.setPosition(sf::Vector2f(50.f, 50.f));

		// We make sure that the player did not take damage
		EXPECT_EQ(playerTest->getCurrentHealth(), playerTest->getMaxHealth());

		// We move the player to its own bullet
		playerTest->setPosition(position);
		stage.playerProjectileCheckCollisions(allyProjectile);

		// The player should not have take damage
		EXPECT_EQ(playerTest->getCurrentHealth(), playerTest->getMaxHealth());

		// We do the same for the enemy and its bullet
		enemyTest.setPosition(position2);
		stage.addEnemy(std::move(enemyTest));
		stage.enemyProjectileCheckCollisions(enemyProjectile);
		EXPECT_EQ(enemyTest.getCurrentHealth(), enemyTest.getMaxHealth());

		// Now we check if the bullets can damage the player
		playerTest->setPosition(position2);
		stage.enemyProjectileCheckCollisions(enemyProjectile);
		EXPECT_EQ(playerTest->getCurrentHealth(), playerTest->getMaxHealth() - 10);

		// We do the same for the enemy
		enemyTest.setPosition(allyProjectile.getPosition());
		stage.addEnemy(std::move(enemyTest));
		stage.playerProjectileCheckCollisions(allyProjectile);
		EXPECT_EQ(stage.getEnemyHealth(1), enemyTest.getMaxHealth() - 10);
	}

	TEST(TestMenu, TestWritingJson) {
		// We check that when we write a new value in a Json file it gets correctly updated

		using json = nlohmann::json;

		GameMenu gameMenu{};

		gameMenu.setCurrentSaveFile(0);

		// We first check that the value that we read is the correct one
		std::ifstream f("resources/Entity.json");
		json allData = json::parse(f);
		f.close();

		EXPECT_EQ(allData.at("player1").at("damageUpgrade"), 0);

		// We have changed the first upgrade, in this case the damage upgrade
		gameMenu.updateUpgradeMenu();

		// We simulate that the player upgrades one of its stats
		gameMenu.setUpgradeLevel(0, 1);
		gameMenu.updateJson(0);

		std::ifstream f2("resources/Entity.json");
		json allData2 = json::parse(f2);
		f2.close();

		EXPECT_EQ(allData2.at("player1").at("damageUpgrade"), 1);

		// We make sure to clean up the Json after modifying it in order to not mess with other tests
		std::ifstream f3("resources/Entity.json");
		json allData3 = json::parse(f3);
		f3.close();

		allData3["player1"]["baseDamage"] = 35;
		allData3["player1"]["damageUpgrade"] = 0;

		std::ofstream fout("resources/Entity.json");

		fout << allData3.dump(4);
		
		fout.flush();
		fout.close();
	}
}

