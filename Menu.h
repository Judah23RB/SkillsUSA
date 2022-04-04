#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include <vector>
class Menu
{
public:

	Menu();
	~Menu();

	void setWindow(sf::RenderWindow&);

	//Utility
	void clearOptions();

	//menus
	int startMenu();
	int levelMenu();
	int settingsMenu();
	int wonMenu();
	int lostMenu();
	
	//textures
	void loadBackground(sf::Sprite&);
	void loadScoreSheet(sf::Texture*);

	//Music!!!!
	void loadMusic(sf::Music&);
	
	//Animations
	void startAnimation();
	void gameOverAnimation(bool); //won or lost
	
	//levels Menu
	bool isUnlocked(int);
	void unlockLevel(int);

	//scores
	void loadScores(int[]); //reads in levelScores from game, converts to star score system
	void displayScores();

private:
	std::vector<Button> buttons;
	bool unlocked[8] = { true,false,false,false,false,false,false,false };
	int scores[8] = { 0,0,0,0,0,0,0,0 }; //compared to and updated by load scores
	sf::RenderWindow* screen = nullptr;
	sf::Font font;
	sf::Text title, win, lose;
	sf::Sprite* background = nullptr;
	sf::Sprite scoreStars;

	bool mainMenu = false; //used for displaying title
	bool levMenu = false; //used for displaying level scores

	int inputs();
	void startOptions();
	void levelOptions();
	void settingsOptions();
	void wonOptions();
	void lostOptions();
};