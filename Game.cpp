#include "Game.h"
#include <time.h>


Game::Game()
{
	initWindow();
	initLevels();
	initTextures();
	initSounds();
	
	if (!font.loadFromFile("ARCADECLASSIC.ttf"))
		std::cout << "Error loading font" << std::endl;
	
	menu.setWindow(window);
	
	
	win.setFont(font);
	lose.setFont(font);
	
	win.setFillColor(sf::Color::Green);
	lose.setFillColor(sf::Color::Red);
	
	win.setString("YOU WIN!");
	lose.setString("YOU LOSE");
	
	win.setCharacterSize(80);
	lose.setCharacterSize(80);
	
	win.setOrigin(win.getCharacterSize() / 2, win.getCharacterSize() / 2);
	lose.setOrigin(lose.getCharacterSize() / 2, lose.getCharacterSize() / 2);
	
	win.setPosition(200, 400);
	lose.setPosition(200, 400);
}

Game::~Game()
{

}

void Game::initWindow()
{
	window.create(sf::VideoMode(600, WINDOWSIZE), "Allegory", sf::Style::Close);
	window.setFramerateLimit(144);
}

void Game::initLevels()
{
	//will eventully initialize all levels in similar way
	levels[0].loadLevel("1");
	levels[1].loadLevel("2");
	levels[2].loadLevel("3");
	levels[3].loadLevel("4");
	levels[4].loadLevel("5");
}

void Game::initTextures()
{
	if (!platTextSheet.loadFromFile("Sprites/Platforms.jpg"))
		std::cout << "Error loading platform texture" << std::endl;
	
	if (!background.loadFromFile("Sprites/Background.jpg"))
		std::cout << "Error loading platform texture" << std::endl;

	if (!playerImage.loadFromFile("Sprites/Player_Sprite_Sheet.png"))
		std::cout << "Error loading Player Texture" << std::endl;

	if (!itemSheet.loadFromFile("Sprites/ItemSheet.png"))
		std::cout << "Error loading Item Texture" << std::endl;

	if (!healthSheet.loadFromFile("Sprites/Hearts.png"))
		std::cout << "Error loading Hearts Texture" << std::endl;

	if (!scoreSheet.loadFromFile("Sprites/stars.png"))
		std::cout << "Error loading score stars texture" << std::endl;

	playerImage.createMaskFromColor(sf::Color(255, 255, 255), 0); //needed to make texture background transparant


	backgroundImage.setTexture(background);
	menu.loadBackground(backgroundImage);
	sf::Texture* scoreTextPtr = &scoreSheet;
	menu.loadScoreSheet(scoreTextPtr);
	
	
	//holds platforms
	const sf::Texture* textureptr = &platTextSheet;
	levelTexts.push_back(textureptr);
	
	//items
	textureptr = &itemSheet;
	levelTexts.push_back(textureptr);
	
	//player
	sf::Texture* playerTextureptr = &playerTexts;
	playerTexts.loadFromImage(playerImage);
	player.setTexture(playerTextureptr);

	//health
	health.setTexture(healthSheet);
	sf::IntRect hearts3(0, 0, 49, 12);
	health.setScale(2, 2);
	health.setTextureRect(hearts3);
	
	
	
	//will eventually load all textures in same way
	levels[0].loadTexture(levelTexts);
	levels[1].loadTexture(levelTexts);
	levels[2].loadTexture(levelTexts);
	levels[3].loadTexture(levelTexts);
	levels[4].loadTexture(levelTexts);
}

void Game::initSounds()
{
	if (!gameMusic.openFromFile("AudioFiles/GameMusic.ogg"))
		std::cout << "Error loading game Music" << std::endl;

	if (!menuMusic.openFromFile("AudioFiles/GameMusic.ogg"))
		std::cout << "Error loading Menu music" << std::endl;

}

void Game::runMainMenu()
{
	int choice = NULL;
	int levelChoice;
	choice = menu.startMenu();
	switch (choice)
	{
	case 1:
		runLevelMenu();
		choice = 0;
		break;
	case 2:
		//settings will allow turning off of music
		choice = 0;
		break;
	case 3:
		window.close();
		break;
	default:
		break;
	}
	window.display();
}

void Game::runLostMenu()
{
	window.clear();
	window.display();
	resetLevels();
	delay(500);
	
	int choice = menu.lostMenu();
	switch (choice)
	{
	case 4: //play Level Again
		playLevel(currentLevel);
		break;
	case 5: //return to main menu
		runLevelMenu();
		break;
	case 6:
		window.close();
		break;
	default:
		break;
	}
	window.display();
}

void Game::runWonMenu()
{
	window.clear();
	window.display();
	delay(500);
	
	resetLevels();
	menu.unlockLevel(currentLevel + 1); 
	int choice = menu.wonMenu();
	switch (choice)
	{
	case 7: //play next level
		window.clear();
		currentLevel++;
		choice = 0;
		
		playLevel(currentLevel); 
		break;
	case 8: //return to main menu
		window.clear();
		runLevelMenu();
		break;
	case 9:
		window.close();
		break;
	default:
		break;
	}
	//window.display();
}


void Game::runLevelMenu()
{
	int levelChoice;
	window.clear();
	levelChoice = menu.levelMenu();
	if (levelChoice == 15) //back
		runMainMenu();
	else if (menu.isUnlocked(levelChoice - 9))
		playLevel(levelChoice - 9);
}


void Game::drawSprites(Level &level)
{
	window.draw(backgroundImage);
	window.draw(health);
	window.draw(player.getPlaySprite());
	level.drawLevel(window);
}

void Game::updateHealth()
{
	health.setPosition(sf::Vector2f(0, 0));
	
	sf::IntRect hearts3(0,0,49,12);
	sf::IntRect hearts2(0,16,49,12);
	sf::IntRect hearts1(0,32,49,12);
	sf::IntRect hearts0(0,48,49,12);

	switch (player.getHealth())
	{
	case 3:
		health.setTextureRect(hearts3);
		break;
	case 2:
		health.setTextureRect(hearts2);
		break;
	case 1:
		health.setTextureRect(hearts1);
		break;
	case 0:
		health.setTextureRect(hearts0);
		break;
	default:
		health.setTextureRect(hearts0);
		break;
	}
}

//Player will fall as Level Scrolls until player loses
//handles platform and item collision
void Game::falling(Level &level)
{
	int platType = 0;
	if(!loss(level))
	{
		updateHealth();
		itemCollision(level,currentLevel); //independent of player physics
		player.horizMoveModifier(0); //resets player movement speed
							  
		// if in bounds and not colliding, player falls as window scrolls
		if (player.getPosition().y < WINDOWSIZE && !level.collision(player.getPlayerBounds(), platType))
		{
			fallState = true;
			player.updatePhysics(); //make player fall according to gravity
			level.scrollLevel(window);
			
		}
		else //if colliding, player scrolls with platforms according to platform type
		{
			fallState = false;
			
			//checks to see how long player has been falling
			if (fallClock.getElapsedTime().asSeconds() > 1.25)
				player.updateHealth(-1); //minor damage
			else if (fallClock.getElapsedTime().asSeconds() > 2)
				player.updateHealth(-2); //major damage
			else if (fallClock.getElapsedTime().asSeconds() > 2.5)
				player.updateHealth(-3); //auto kills

			
			
			//std::cout << player.getHealth() << std::endl;
			
			//checks type of collided platform for effect on player
			switch (platType)
			{
			case 1: //base
				player.resetYVelocity();
				player.collide(level.getScrollSpeed());
				fallClock.restart();
				break;
			case 2:
				//continues to fall, platform animation handled in level?
				break;
			case 3: //tread left
				player.horizMoveModifier(-.5);
				player.resetYVelocity();
				player.collide(level.getScrollSpeed());
				player.move(-1, 0);
				player.updatePhysics();
				fallClock.restart();
				break;
			case 4: //tread right
				player.horizMoveModifier(.5);
				player.resetYVelocity();
				player.collide(level.getScrollSpeed());
				player.move(1, 0);
				player.updatePhysics();
				fallClock.restart();
				break;
			case 5: //spike auto kills
				player.setHealth(0);
				break;
			case 6: //end plat, victory condition handled seperatly 
				player.resetYVelocity();
				player.collide(level.getScrollSpeed());
				fallClock.restart();
				break;
			default:
				break;
			}
			
			level.scrollLevel(window);
		}
	}
}
//handles player and game impact of item collision
void Game::itemCollision(Level& level, int levNum)
{
	int item = 0;
	if (level.itemCollision(player.getPlayerBounds(), item))
	{
		switch (item)
		{
		case 1:
			levelScores[levNum - 1] += 100;
			break;
		case 2:
			if (player.getHealth() != 3)
				player.updateHealth(1);
			break;
		case 3:
			level.changeScrollSpeed(level.getScrollSpeed() + .025);
			break;
		case 4:
			wonLevel = true;
			break;

		}
	}
}


//holds game loop, won and lost menu
//winning results in the next level being made accessible
//losing resets the current level
void Game::movement(Level &level)
{
	gameClock.restart();
	lostLevel = wonLevel = false;
	while (window.isOpen())
	{
		if (!wonLevel && !lostLevel) //game loop
		{
			
			lostLevel = loss(level);
	
			falling(level);
			player.moveInput(fallState, level.getScrollSpeed());
			player.updateAnimations();
			
			window.clear();
			drawSprites(level);
			window.display();
			//gameMusic.play();
		}
		else if (wonLevel) //won menu
		{
			updateLevelScores();
			window.clear();
			window.draw(backgroundImage);
			window.draw(win);
			window.display();
			//gameMusic.stop();
			delay(500);
			runWonMenu();

		}
		else if (lostLevel) //loss menu
		{
			
			window.clear();
			window.draw(backgroundImage);
			window.draw(lose);
			window.display();
			//gameMusic.stop();
			delay(500);
			runLostMenu();
		}
		
	}
}

//lose if carried off screen, fall below final platform, or lose all health
bool Game::loss(Level &level)
{
	if (player.getPosition().y < 0 || player.getPosition().y > 700 || player.getHealth() == 0)
		return true;
	return false;
}

void Game::playLevel(int level)
{
	player.setPosition(sf::Vector2f(window.getSize().x / 2, 0));
	window.clear();
	fallClock.restart();
	while (window.isOpen())
	{
		drawSprites(levels[level - 1]);
		movement(levels[level - 1]);
		window.display();
	}
}

void Game::resetLevel(int inp)
{
	std::cout << "Resetting Level" << inp << std::endl;
	lostLevel = wonLevel = false;
	levels[inp - 1].resetLevel();
	player.setHealth(3);
}


//I took the nuclear approach
void Game::resetLevels()
{
	resetLevel(1);
	resetLevel(2);
	resetLevel(3);
	resetLevel(4);
}

//takes into account completion time and health to assign score
//score items affect score in separate function
void Game::updateLevelScores()
{
	//replace with relevant completion times for each level
	switch (currentLevel - 1)
	{
	case 0:
		if (gameClock.getElapsedTime().asSeconds() < 10)
			levelScores[currentLevel - 1] += 1000;
		if (gameClock.getElapsedTime().asSeconds() < 12)
			levelScores[currentLevel - 1] += 750;
		if (gameClock.getElapsedTime().asSeconds() < 15)
			levelScores[currentLevel - 1] += 500;
		break;
	case 1:
		if (gameClock.getElapsedTime().asSeconds() < 10)
			levelScores[currentLevel - 1] += 1000;
		if (gameClock.getElapsedTime().asSeconds() < 12)
			levelScores[currentLevel - 1] += 750;
		if (gameClock.getElapsedTime().asSeconds() < 15)
			levelScores[currentLevel - 1] += 500;
		break;
	case 2: 
		if (gameClock.getElapsedTime().asSeconds() < 10)
			levelScores[currentLevel - 1] += 1000;
		if (gameClock.getElapsedTime().asSeconds() < 12)
			levelScores[currentLevel - 1] += 750;
		if (gameClock.getElapsedTime().asSeconds() < 15)
			levelScores[currentLevel - 1] += 500;
		break;
	case 3:
		if (gameClock.getElapsedTime().asSeconds() < 10)
			levelScores[currentLevel - 1] += 1000;
		if (gameClock.getElapsedTime().asSeconds() < 12)
			levelScores[currentLevel - 1] += 750;
		if (gameClock.getElapsedTime().asSeconds() < 15)
			levelScores[currentLevel - 1] += 500;
		break;
	case 4:
		if (gameClock.getElapsedTime().asSeconds() < 10)
			levelScores[currentLevel - 1] += 1000;
		if (gameClock.getElapsedTime().asSeconds() < 12)
			levelScores[currentLevel - 1] += 750;
		if (gameClock.getElapsedTime().asSeconds() < 15)
			levelScores[currentLevel - 1] += 500;
		break;
	default:
		break;

	}
	
	//include health as part of calculation
	switch (player.getHealth())
	{
	case 3:
		break;
	case 2:
		levelScores[currentLevel - 1] -= 100;
		break;
	case 1:
		levelScores[currentLevel - 1] -= 300;
		break;
	case 0:
		levelScores[currentLevel - 1] = 0;
		break;
	default:
		break;
	}

	convertLevelScores();
}


//converts scores to score stars for display in menu
void Game::convertLevelScores()
{
	//hard coded to account for item impact
	switch (currentLevel - 1)
	{
	case 0:
		if (levelScores[0] >= 1000)
			scoreStarsArr[0] = 3;
		else if (levelScores[0] > 750)
			scoreStarsArr[0] = 2;
		else
			scoreStarsArr[0] = 1;
	case 1:
		if (levelScores[1] >= 1000)
			scoreStarsArr[1] = 3;
		else if (levelScores[1] > 750)
			scoreStarsArr[1] = 2;
		else
			scoreStarsArr[1] = 1;
	case 2:
		if (levelScores[2] >= 1100)
			scoreStarsArr[2] = 3;
		else if (levelScores[2] > 850)
			scoreStarsArr[2] = 2;
		else
			scoreStarsArr[2] = 1;
	case 3:
		if (levelScores[3] >= 1200)
			scoreStarsArr[3] = 3;
		else if (levelScores[3] > 950)
			scoreStarsArr[3] = 2;
		else
			scoreStarsArr[3] = 1;
	case 4:
		break;
	default:
		break;
	}
	
	
	for (int x = 0; x < 4; x++) //change to 5 when final level is loaded in
	{
		if (levelScores[x] == 0)
			scoreStarsArr[x] = 0;
	}
	menu.loadScores(scoreStarsArr);
}

void Game::delay(int inp)
{
	clock_t time1 = clock();
	clock_t time2 = time1 + inp;
	while (time1 < time2)
		time1 = clock();
	return;
}


