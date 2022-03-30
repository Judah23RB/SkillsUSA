#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>


Game::Game()
{
	initWindow();
	initLevels();
	initTextures();
	
	//for (int x = 0; x < 5; x++)
		//backUp[x] = levels[x];
	
	if (!font.loadFromFile("ARCADECLASSIC.ttf"))
		std::cout << "Error loading font" << std::endl;
	
	menu.setWindow(window);
	
	//used for playing levels again, initialize backups after level has been full initialized
	backUp[0] = levels[0];
	
	win.setFont(font);
	lose.setFont(font);
	
	win.setFillColor(sf::Color::Green);
	lose.setFillColor(sf::Color::Red);
	
	win.setString("YOU WIN");
	lose.setString("YOU LOSE");
	
	win.setCharacterSize(50);
	lose.setCharacterSize(50);
	
	win.setOrigin(win.getCharacterSize() / 2, win.getCharacterSize() / 2);
	lose.setOrigin(lose.getCharacterSize() / 2, lose.getCharacterSize() / 2);
	
	win.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	lose.setPosition(window.getSize().x / 2, window.getSize().y / 2);
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
}

void Game::initTextures()
{
	if (!defaultplat.loadFromFile("Sprites/Platforms.jpg"))
		std::cout << "Error loading platform texture" << std::endl;
	
	if (!background.loadFromFile("Sprites/Background.jpg"))
		std::cout << "Error loading platform texture" << std::endl;

	backgroundImage.setTexture(background);
	menu.loadBackground(backgroundImage);

	const sf::Texture* textureptr = &defaultplat;
	levelTexts.push_back(textureptr);


	//will eventually load all textures in same way
	levels[0].loadTexture(levelTexts);
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
		if (menu.isUnlocked(levelChoice - 1))
			playLevel(levelChoice);
		break;
	case 2:
		//settings will allow turning off of music
		break;
	case 3:
		//window.close();
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
void Game::falling(Level &level)
{
	
	if(!loss(level))
	{
		// if in bounds and not colliding, player falls as window scrolls
		if (player.getPosition().y < WINDOWSIZE && !level.collision(player.getPlayerBounds(), &player))
		{
			fallState = true;
			player.updatePhysics(); //make player fall according to gravity
			level.scrollLevel(window);
			
		}
		else
		{
			fallState = false;
			//checks to see how long player has been falling
			if (fallClock.getElapsedTime().asSeconds() > 1)
				player.updateHealth(-1);
			
			std::cout << player.getHealth() << std::endl;
			
			//stop gravity, update physics, have player collide according to scroll speed

			player.resetYVelocity();
			player.collide(level.getScrollSpeed());
			level.scrollLevel(window);
			
			fallClock.restart();
			
		}
	}
}
//holds game loop, won and lost menu
//winning results in the next level being made accessible
//losing resets the current level
void Game::movement(Level &level)
{
	while (window.isOpen())
	{
		if (!won(level)) //game loop
		{
			falling(level);
			player.moveInput(fallState, level.getScrollSpeed());
			
			window.clear();
			window.draw(player.getPlaySprite());
			level.drawLevel(window);
			
			window.display();
		}
		else if (won(level)) //won menu
		{
			window.clear();
			window.display();
			delay(200);
			
			menu.unlockLevel(currentLevel);
			int choice = menu.wonMenu();
			switch (choice)
			{
			case 1:
				window.clear();
				currentLevel++;
				resetLevel(currentLevel - 1);
				playLevel(currentLevel);
				break;
			case 2:
				window.clear();
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
		else if (loss(level)) //loss menu
		{
			window.clear();
			window.display();
			delay(200);
			int choice = menu.lostMenu();
			switch (choice)
			{
			case 1:
				resetLevel(currentLevel);
				playLevel(currentLevel);
				break;
			case 2:
				window.clear();
				window.display();
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
		
	}
}

bool Game::won(Level &level)
{
	Platforms* temp = level.getEndPlat();
	if (player.getPlayerBounds().intersects(temp->getPlatBounds()))
	{
		window.clear();
		window.draw(win);
		window.display();
		
		return true;
	}
	return false;
}

bool Game::loss(Level &level)
{
	if (player.getPosition().y < 0 || player.getPosition().y > level.getEndPlat()->getPos().y + 20 || player.getHealth() == 0)
	{
		window.draw(lose);
		window.display();
		return true;
	}
	
	return false;
}

void Game::playLevel(int level)
{
	player.setPosition(sf::Vector2f(window.getSize().x / 2, 0));
	window.clear();
	fallClock.restart();
	while (window.isOpen())
	{
		drawSprites(levels[0]);
		movement(levels[0]);
		window.display();
	}
}

void Game::resetLevel(int inp)
{
	levels[inp - 1] = backUp[inp - 1];
	player.setPosition(sf::Vector2f(300, 10));
	fallClock.restart();
}


void Game::delay(int inp)
{
	clock_t time1 = clock();
	clock_t time2 = time1 + inp;
	while (time1 < time2)
		time1 = clock();
	return;
}


