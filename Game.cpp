#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>


Game::Game()
{
	initWindow();
	initLevels();
	
	//for (int x = 0; x < 5; x++)
		//backUp[x] = levels[x];
	
	if (!font.loadFromFile("ARCADECLASSIC.ttf"))
		std::cout << "Error loading font" << std::endl;
	
	if (!defaultplat.loadFromFile("Sprites/Default.png"))
		std::cout << "Error loading platform texture" << std::endl;


	menu.setWindow(window);
	
	const sf::Texture* textureptr = &defaultplat;
	
	levels[0].loadTexture(textureptr);
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
}

void Game::initLevels()
{
	levels[0].loadLevel("1");
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
	window.draw(player.getPlaySprite());
	
	level.drawLevel(window);
}

void Game::playerMovement()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		int moveSpeed;
		
		if (fallState)
			moveSpeed = 5;
		else 
			moveSpeed = 10;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (player.getPosition().x > 0)
				player.moveLeft(moveSpeed);
			started = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (player.getPosition().x < 600)
				player.moveRight(moveSpeed);
			started = true;
		}
		window.clear();
	}
	
}
//Player will fall as Level Scrolls until player loses
//if player loses, displays LostMenu, allowing them to try again, return to Main, or Quit

void Game::falling(Level &level)
{
	if(!loss(level))
	{
		if (player.getPosition().y < WINDOWSIZE && !level.collision(player.getPlayerBounds()))
		{
			player.fall();
			level.scrollLevel(window);
			fallState= true;
		}
		else
		{
			player.collide(level.getScrollSpeed());
			level.scrollLevel(window);
			fallState = false;
		}
		window.clear();
		window.draw(player.getPlaySprite());
		level.drawLevel(window);
		window.display();
	}
	else
	{
		window.clear();
		window.display();
		delay(200);
		int choice = menu.lostMenu();
		switch (choice)
		{
		case 1:
			resetLevel();
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

void Game::movement(Level &level)
{
	while (window.isOpen())
	{
		if (!won(level))
		{
			playerMovement();
			falling(level);
		}
		else
		{
			window.clear();
			window.display();
			delay(200);
			menu.unlockLevel(currentLevel + 1);
			int choice = menu.wonMenu();
			switch (choice)
			{
			case 1:
				window.clear();
				currentLevel++;
				resetLevel();
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
	if (player.getPosition().y < 0 || player.getPosition().y > level.getEndPlat()->getPos().y + 20)
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
	while (window.isOpen())
	{
		drawSprites(levels[0]);
		movement(levels[0]);
		window.display();
	}
}

void Game::resetLevel()
{
	for (int x = 0; x < 5; x++)
		levels[x] = backUp[x];
}


void Game::delay(int inp)
{
	clock_t time1 = clock();
	clock_t time2 = time1 + inp;
	while (time1 < time2)
		time1 = clock();
	return;
}


