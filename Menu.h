#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <vector>
class Menu
{
public:

	Menu();
	~Menu();

	void setWindow(sf::RenderWindow&);


	//menus
	int startMenu();
	int levelMenu();
	int settingsMenu();
	int wonMenu();
	int lostMenu();
	
	//textures
	void loadBackground(sf::Sprite&);
	
	//Animations
	void startAnimation();
	void gameOverAnimation(bool); //won or lost
	
	//levels Menu
	bool isUnlocked(int);
	void unlockLevel(int);

private:
	std::vector<Button> buttons;
	bool unlocked[5] = {true,false,false,false,false};
	sf::RenderWindow* screen = nullptr;
	sf::Font font;
	sf::Text title;
	sf::Sprite* background = nullptr;

	bool mainMenu = true; //used for displaying title

	int inputs();
	void startOptions();
	void levelOptions();
	void settingsOptions();
	void wonOptions();
	void lostOptions();
};

