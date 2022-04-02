#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Platforms.h"
#include "Player.h"
#include "Item.h"
class Level
{
public:
	
	Level();
	~Level();
	
	void loadLevel(std::string); //reads in using folder name as string
	void initLevel();
	void resetLevel(); //used after level is completed/failed

	void loadTexture(std::vector<const sf::Texture*>);
	
	void animateBrokePlat(Platforms&);
	
	int getPlatNum();
	bool collision(sf::FloatRect, int&); //passes in boundary box, storage int that is set to platform type 
	bool itemCollision(sf::FloatRect, int&); //boundary box, int set to item type if collision occurs
	void drawLevel(sf::RenderWindow&);
	
	Platforms* getEndPlat();
	void scrollLevel(sf::RenderWindow&);
	void levelProgression();
	void changeScrollSpeed(double);

	double getScrollSpeed(); // used for collision
private:
	int platNum = 0;
	int itemNum = 0;
	double scrollSpeed = -.25;
	bool noItems = false;
	std::string levNum; // reading in data
	
	std::vector<int> xvals, yvals, length, platTypes; //platform data
	std::vector<int> iXVals, iYVals, iType; //item data
	
	Platforms* leveldata = nullptr; //heap array
	Item* itemData = nullptr; //heap array
	Platforms* endPlat = nullptr;

	
	
};

