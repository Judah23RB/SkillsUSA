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

	int startMenu();
	int levelMenu();
	int settingsMenu();
	int wonMenu();
	int lostMenu();

	bool isUnlocked(int);
	void unlockLevel(int);

private:
	std::vector<Button> buttons;
	bool unlocked[5] = {true,false,false,false,false};
	sf::RenderWindow* screen = nullptr;
	sf::Font font;

	int inputs();
	void startOptions();
	void levelOptions();
	void settingsOptions();
	void wonOptions();
	void lostOptions();




};
