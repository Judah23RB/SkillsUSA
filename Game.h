#pragma once
#include "Player.h"
#include "Platforms.h"
#include "Level.h"
#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <SFML/Audio.hpp>

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
	int score = 0;
	bool lostLevel, wonLevel;
	
	sf::RenderWindow window;
	sf::Font font;
	sf::Texture platTextSheet, background, playerTexts, itemSheet;
	sf::Image playerImage, itemImage;
	sf::Sprite backgroundImage;
	sf::Text win, lose;
	sf::Clock fallClock;
	sf::SoundBuffer* soundbuffer = nullptr;
	sf::Music menuMusic, gameMusic;

	Menu menu;
	Player player;
	
	Level levels[5];

	std::vector<sf::Sound> sounds; //0 is score, 1 is health, 2 is slow fall, 3 is fall damage, 4 is win, 5 is lose
	std::vector<const sf::Texture*> levelTexts; //holds pointers to sprite sheets needed for level
	
	void initLevels();
	void initWindow();
	void initTextures();
	void initSounds();
	
	void falling(Level&);
	void itemCollision(Level&);

	bool won(Level&);
	bool loss(Level&);

	void resetLevel(int);

	void delay(int);
};

