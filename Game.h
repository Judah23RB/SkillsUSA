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
	void runLevelMenu();
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
	sf::Texture platTextSheet, background, playerTexts, itemSheet, healthSheet, scoreSheet, soundSprites;
	sf::Image playerImage;
	sf::Sprite backgroundImage, health, scores;
	sf::Text win, lose;
	sf::Clock fallClock, gameClock;
	
	sf::SoundBuffer* soundbuffer = nullptr;
	sf::Time soundDelay = sf::seconds(.1);

	Menu menu;
	Player player;
	
	Level levels[8];
	int levelScores[8] = { 0,0,0,0,0,0,0,0 }; //loads in raw time values
	int scoreStarsArr[8] = { 0,0,0,0,0,0,0,0 }; //uses levelScores, accounts for 0 not completed, 1 bronze, 2 silver, 3 gold

	std::vector<sf::Sound> sounds; //0 is score, 1 is health, 2 is slow fall, 3 is fall damage, 4 is win, 5 is lose
	std::vector<const sf::Texture*> levelTexts; //holds pointers to sprite sheets needed for level
	
	void initLevels();
	void initWindow();
	void initTextures();
	void initSounds();
	
	void falling(Level&);
	void itemCollision(Level&, int);

	void updateHealth();
	bool loss(Level&);

	void resetLevel(int);
	void resetLevels();
	void updateLevelScores();
	void convertLevelScores();

	void updateSoundVolume(int);

	void delay(int);
};