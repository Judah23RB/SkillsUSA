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
	
	
	void runMainMenu();
	void runLevelMenu();
	void playLevel(int);
	void drawSprites(Level&);
	void movement(Level&);
	
	
private:
	const static int WINDOWSIZE = 1000;
	
	bool started = false;
	bool fallState;
	int currentLevel = 0;
	sf::RenderWindow window;
	sf::Font font;
	sf::Texture defaultplat;
	sf::Text win, lose;
	
	Menu menu;
	Player player;
	
	Level levels[5];
	Level backUp[5];
	
	void initLevels();
	void initWindow();
	//called by movement
	void playerMovement();
	void falling(Level&);

	bool won(Level&);
	bool loss(Level&);

	void resetLevel();

	void delay(int);
};

