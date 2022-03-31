#pragma once
#include "Player.h"
#include "Platforms.h"
#include "Level.h"
#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

class Game
{
public:
	Game();
	~Game();
	
	
	void runMainMenu(); //level and settings menu handled within main
	void runLostMenu();
	void runWonMenu();
	void playLevel(int);
	void drawSprites(Level&);
	void movement(Level&);
	
	
private:
	const static int WINDOWSIZE = 1000;
	
	bool fallState;
	int currentLevel = 1;
	
	sf::RenderWindow window;
	sf::Font font;
	sf::Texture platTextSheet, background, playerTexts;
	sf::Image playerImage;
	sf::Sprite backgroundImage;
	sf::Text win, lose;
	sf::Clock fallClock;
	
	Menu menu;
	Player player;
	
	Level levels[5];

	
	std::vector<const sf::Texture*> levelTexts; //holds pointers to sprite sheets needed for level
	
	void initLevels();
	void initWindow();
	void initTextures();
	
	void falling(Level&);

	bool won(Level&);
	bool loss(Level&);

	void resetLevel(int);

	void delay(int);
};

