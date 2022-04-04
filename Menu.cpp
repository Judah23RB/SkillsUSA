#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	if (!font.loadFromFile("ARCADECLASSIC.ttf"))
		throw "Error Loading Font\n";

	title.setFont(font);
	title.setCharacterSize(64);
	title.setFillColor(sf::Color(128, 128, 128));
	title.setOutlineThickness(5);
	title.setOutlineColor(sf::Color::Black);

	title.setPosition(160, 20);
	title.setString("  DESCENT\n\t\tINTO\nDARKNESS");
	title.setLetterSpacing(1.1);
}

void Menu::setWindow(sf::RenderWindow& window)
{
	screen = &window;
}

void Menu::clearOptions()
{
	buttons.clear();
}

void Menu::loadBackground(sf::Sprite& image)
{
	background = &image;
}

void Menu::loadScoreSheet(sf::Texture* textptr)
{
	scoreStars.setTexture(*textptr);
	scoreStars.setScale(2, 2);
}
Menu::~Menu()
{

}

int Menu::startMenu()
{
	mainMenu = true;
	levMenu = false;
	buttons.clear();
	screen->clear();
	startOptions();
	return inputs();
}

int Menu::levelMenu()
{
	levMenu = true;
	mainMenu = false;
	screen->clear();
	levelOptions();
	return inputs();
}
/*
int Menu::settingsMenu()
{
	screen->clear();
	settingsOptions();
	return inputs();
}
*/

int Menu::wonMenu()
{
	mainMenu = false;
	levMenu = false;
	screen->clear();
	wonOptions();
	return inputs();
}

int Menu::lostMenu()
{
	mainMenu = false;
	levMenu = false;
	screen->clear();
	lostOptions();
	return inputs();
}

int Menu::inputs()
{
	int input = 0;
	sf::Event e;
	screen->clear();
	
	while (input == 0)
	{
		screen->draw(*background);
		
		if (mainMenu)
			screen->draw(title);

		if (levMenu)
			displayScores();
		
		for (auto i : buttons)
			screen->draw(i);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (auto i : buttons)
			{
				sf::FloatRect bounds = i.getBounds();
				if (bounds.contains(sf::Vector2f(sf::Mouse::getPosition(*screen))))
					input = i.getValue();
			}
		}

		while (screen->pollEvent(e))
			if (e.type == sf::Event::Closed)
				screen->close();

		screen->display();
	}
	buttons.clear();
	return input;
}

//adds buttons to vector, play pulls up levelMenu, settings pulls up Setting Menu, Quit quits
void Menu::startOptions()
{
	buttons.clear();
	
	Button temp("", 0, font);
	
	temp = Button("Play", 1, font);
	temp.setPosition(100, screen->getSize().y * .25);
	temp.setColor(sf::Color(128, 128, 128));
	
	buttons.push_back(temp);

	temp = Button("Settings", 2, font);
	temp.setPosition(100, screen->getSize().y * .5);
	temp.setColor(sf::Color(128, 128, 128));
	buttons.push_back(temp);

	temp = Button("Quit", 3, font);
	temp.setPosition(100, screen->getSize().y * .75);
	temp.setColor(sf::Color(128, 128, 128));
	buttons.push_back(temp);
}


//holds menu buttons for levels, if a level is completed, the next level is unlocked
void Menu::levelOptions()
{
	buttons.clear();
	

	Button temp("", 0, font);
	sf::RectangleShape buttonShape(sf::Vector2f(70, 70));
	sf::Color locked(sf::Color(128, 128, 128));
	sf::Color unlockedColor(sf::Color::White);
	const int levelTextSize = 64;

	temp = Button("1", 10, font, buttonShape,levelTextSize);
	temp.setPosition(125, screen->getSize().y / 2 - 100);
	if (!unlocked[0])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	
	buttons.push_back(temp);

	temp = Button("2",11, font, buttonShape,levelTextSize);
	temp.setPosition(225, screen->getSize().y / 2 - 100);
	if (!unlocked[1])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	buttons.push_back(temp);

	temp = Button("3", 12, font, buttonShape,levelTextSize);
	temp.setPosition(325, screen->getSize().y / 2 - 100);
	if (!unlocked[2])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	buttons.push_back(temp);
	
	temp = Button("4", 13, font, buttonShape,levelTextSize);
	temp.setPosition(425, screen->getSize().y / 2 - 100);
	if (!unlocked[3])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	buttons.push_back(temp);

	temp = Button("5", 14, font, buttonShape,levelTextSize);
	temp.setPosition(125, screen->getSize().y / 2  + 200);
	if (!unlocked[4])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	buttons.push_back(temp);
	
	temp = Button("6", 15, font, buttonShape, levelTextSize);
	temp.setPosition(225, screen->getSize().y / 2 + 200);
	if (!unlocked[4])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	buttons.push_back(temp);

	temp = Button("7", 16, font, buttonShape, levelTextSize);
	temp.setPosition(325, screen->getSize().y / 2 + 200);
	if (!unlocked[4])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	buttons.push_back(temp);

	temp = Button("8", 17, font, buttonShape, levelTextSize);
	temp.setPosition(425, screen->getSize().y / 2 + 200);
	if (!unlocked[4])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	buttons.push_back(temp);
	
	
	temp = Button("Back", 18, font, sf::RectangleShape(sf::Vector2f(80,40)),36);
	temp.setPosition(0, 0);
	temp.setColor(unlockedColor);
	buttons.push_back(temp);
	
}

void Menu::wonOptions()
{
	buttons.clear();

	Button temp("", 0, font);

	temp = Button("Next Level", 7, font);
	temp.setPosition(100, screen->getSize().y * .25);
	buttons.push_back(temp);

	temp = Button("Menu", 8, font);
	temp.setPosition(100, screen->getSize().y  * .5);
	buttons.push_back(temp);

	temp = Button("Quit", 9, font);
	temp.setPosition(100, screen->getSize().y * .75);
	buttons.push_back(temp);

}

void Menu::lostOptions()
{
	buttons.clear();
	screen->clear();

	Button temp("", 0, font);

	temp = Button("Play Again", 4, font);
	temp.setPosition(100, screen->getSize().y * .25);
	buttons.push_back(temp);

	temp = Button("Menu", 5, font);
	temp.setPosition(100, screen->getSize().y * .5);
	buttons.push_back(temp);

	temp = Button("Quit", 6, font);
	temp.setPosition(100, screen->getSize().y * .75);
	buttons.push_back(temp);
}

bool Menu::isUnlocked(int level)
{
	if (unlocked[level - 1])
		return true;
	return false;
}

void Menu::unlockLevel(int level)
{
	unlocked[level - 1] = true;
}

void Menu::loadScores(int scoreArr[])
{
	for (int x = 0; x < 8; x++) //change to levnum - 1
	{
		if (scoreArr[x] > scores[x])
			scores[x] = scoreArr[x];
	}
}



//set sprite texture depending on value of scores
//draw sprite above each level button
void Menu::displayScores()
{
	sf::Sprite lev[8];
	
	for (int x = 0; x < 8; x++)
		lev[x] = scoreStars;

	
	sf::IntRect starsNo(7,3,35,14);
	sf::IntRect stars1(7,23,35,14);
	sf::IntRect stars2(7,42,35,14);
	sf::IntRect stars3(7,62,35,14);

	lev[0].setPosition(125, screen->getSize().y / 2 - 125);
	lev[1].setPosition(225, screen->getSize().y / 2 - 125);
	lev[2].setPosition(325, screen->getSize().y / 2 - 125);
	lev[3].setPosition(425, screen->getSize().y / 2 - 125);
	lev[4].setPosition(125, screen->getSize().y / 2 + 150);
	lev[5].setPosition(225, screen->getSize().y / 2 + 150);
	lev[6].setPosition(325, screen->getSize().y / 2 + 150);
	lev[7].setPosition(425, screen->getSize().y / 2 + 150);

	for (int x = 0; x < 8; x++)
	{
		if (scores[x] == 0)
			lev[x].setTextureRect(starsNo);
		if (scores[x] == 1)
			lev[x].setTextureRect(stars1);
		if (scores[x] == 2)
			lev[x].setTextureRect(stars2);
		if (scores[x] == 3)
			lev[x].setTextureRect(stars3);
	}

	for (int x = 0; x < 8; x++)
		screen->draw(lev[x]);
}

void Menu::gameOverAnimation(bool result)
{
	win.setFont(font);
	lose.setFont(font);

	win.setFillColor(sf::Color::Green);
	lose.setFillColor(sf::Color::Red);

	win.setString("YOU WIN!");
	lose.setString("YOU LOSE");

	win.setCharacterSize(80);
	lose.setCharacterSize(80);

	win.setOrigin(win.getCharacterSize() / 2, win.getCharacterSize() / 2);
	lose.setOrigin(lose.getCharacterSize() / 2, lose.getCharacterSize() / 2);

	win.setPosition(200, 400);
	lose.setPosition(200, 400);

	
	screen->draw(*background);
	if (result)
		screen->draw(win);
	else
		screen->draw(lose);
	screen->display();
}
