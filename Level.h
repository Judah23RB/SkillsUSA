#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Platforms.h"
class Level
{
public:
	
	Level();
	~Level();
	
	void loadLevel(std::string); //reads in using folder name as string
	
	void initLevel();
	void loadTexture(const sf::Texture*);
	void loadTexture(std::vector<const sf::Texture*>);
	
	int getPlatNum();
	bool collision(sf::FloatRect);
	void drawLevel(sf::RenderWindow&);
	
	Platforms* getEndPlat();
	void scrollLevel(sf::RenderWindow&);
	void levelProgression();

	double getScrollSpeed(); // used for collision
private:
	int platNum = 0;
	double scrollSpeed = -.1;
	std::string levNum; // reading in data
	
	std::vector<int> xvals, yvals, length, platTypes;
	sf::Vector2f windowsize;
	Platforms* leveldata = nullptr;
	Platforms* endPlat = nullptr;
	void changeScrollSpeed(double);

};

