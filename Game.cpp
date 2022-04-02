#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>


Game::Game()
{
	initWindow();
	initLevels();
	initTextures();
	
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
		std::cout << "Error loading Player Texture" << std::endl;

	playerImage.createMaskFromColor(sf::Color(255, 255, 255), 0); //needed to make texture background transparant


	backgroundImage.setTexture(background);
	menu.loadBackground(backgroundImage);

	
	
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


	
	
	
	//will eventually load all textures in same way
	std::cout << levelTexts.size() << std::endl;
	levels[0].loadTexture(levelTexts);
	levels[1].loadTexture(levelTexts);
	levels[2].loadTexture(levelTexts);
	levels[3].loadTexture(levelTexts);
	levels[4].loadTexture(levelTexts);
}

void Game::runMainMenu()
{
	int levelChoice;
	int choice = menu.startMenu();
	switch (choice)
	{
	case 1:
		window.clear();
		window.display();
		levelChoice = menu.levelMenu();
		if (levelChoice == 6) //back
			runMainMenu();
		else if (menu.isUnlocked(levelChoice - 1))
			playLevel(levelChoice - 1);
		levelChoice = 0;
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
	delay(500);
	resetLevel(currentLevel - 1);
	
	int choice = menu.lostMenu();
	switch (choice)
	{
	case 1: //play Level Again
		resetLevel(currentLevel - 1);
		playLevel(currentLevel - 1);
		break;
	case 2:
		resetLevel(currentLevel - 1);
		runMainMenu();
		break;
	case 3:
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

	menu.unlockLevel(currentLevel); //1
	int choice = menu.wonMenu();
	switch (choice)
	{
	case 1:
		window.clear();
		currentLevel++;
		choice = 0;
		resetLevel(currentLevel - 2); //0 in level data is level 1
		playLevel(currentLevel - 1); //play level 2
		break;
	case 2:
		window.clear();
		choice = 0;
		resetLevel(currentLevel - 2);
		runMainMenu();
		break;
	case 3:
		window.close();
		break;
	default:
		break;
	}
	window.display();
}



void Game::drawSprites(Level &level)
{
	window.draw(backgroundImage);
	window.draw(player.getPlaySprite());
	level.drawLevel(window);
}

//Player will fall as Level Scrolls until player loses
//handles platform and item collision
void Game::falling(Level &level)
{
	int platType = 0;
	if(!loss(level))
	{
		itemCollision(level); //independent of player physics
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
			if (fallClock.getElapsedTime().asSeconds() > 2)
				player.updateHealth(-1); //minor damage
			else if (fallClock.getElapsedTime().asSeconds() > 4)
				player.updateHealth(-2); //major damage
			else if (fallClock.getElapsedTime().asSeconds() > 6)
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
void Game::itemCollision(Level& level)
{
	int item = 0;
	if (level.itemCollision(player.getPlayerBounds(), item))
	{
		switch (item)
		{
		case 1:
			score += 100;
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
	lostLevel = wonLevel = false;
	while (window.isOpen())
	{
		if (!wonLevel && !lostLevel) //game loop
		{
			//wonLevel handled in item collision
			wonLevel = won(level);
			lostLevel = loss(level);
			
			falling(level);
			player.moveInput(fallState, level.getScrollSpeed());
			player.updateAnimations();
			
			window.clear();
			drawSprites(level);
			window.display();
		}
		else if (wonLevel) //won menu
		{
			window.clear();
			window.draw(backgroundImage);
			window.draw(win);
			window.display();
			delay(500);
			runWonMenu();

		}
		else if (lostLevel) //loss menu
		{
			window.clear();
			window.draw(backgroundImage);
			window.draw(lose);
			window.display();
			delay(500);
			runLostMenu();
		}
		
	}
}
//win if reach designated platform
bool Game::won(Level &level)
{
	Platforms* temp = level.getEndPlat();
	if (player.getPlayerBounds().intersects(temp->getPlatBounds()))
	{
		if (player.getHealth() != 0)
			return true;
	}
	return false;
}
//lose if carried off screen, fall below final platform, or lose all health
bool Game::loss(Level &level)
{
	if (player.getPosition().y < 0 || player.getPosition().y > level.getEndPlat()->getPos().y + 20 || player.getHealth() == 0)
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
		drawSprites(levels[level]);
		movement(levels[level]);
		window.display();
	}
}

void Game::resetLevel(int inp)
{
	levels[inp].resetLevel();
	player.setHealth(3);
}


void Game::delay(int inp)
{
	clock_t time1 = clock();
	clock_t time2 = time1 + inp;
	while (time1 < time2)
		time1 = clock();
	return;
}


