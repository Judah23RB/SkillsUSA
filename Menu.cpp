#include "Menu.h"


Menu::Menu()
{
	if (!font.loadFromFile("ARCADECLASSIC.ttf"))
		throw "Error Loading Font\n";
}

void Menu::setWindow(sf::RenderWindow& window)
{
	screen = &window;
}

void Menu::loadBackground(sf::Sprite& image)
{
	background = &image;
}
Menu::~Menu()
{

}

int Menu::startMenu()
{
	screen->clear();
	startOptions();
	return inputs();
}

int Menu::levelMenu()
{
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
	screen->clear();
	wonOptions();
	return inputs();
}

int Menu::lostMenu()
{
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
	return input;
}

//adds buttons to vector, play pulls up levelMenu, settings pulls up Setting Menu, Quit quits
void Menu::startOptions()
{
	buttons.clear();
	screen->clear();
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
	screen->clear();

	Button temp("", 0, font);
	sf::RectangleShape buttonShape(sf::Vector2f(60, 60));
	sf::Color locked(sf::Color(128, 128, 128));
	sf::Color unlockedColor(sf::Color::White);

	temp = Button("1", 1, font, buttonShape);
	temp.setPosition(75, screen->getSize().y / 2);
	if (!unlocked[0])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	
	buttons.push_back(temp);

	temp = Button("2", 2, font, buttonShape);
	temp.setPosition(175, screen->getSize().y / 2);
	if (!unlocked[1])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	buttons.push_back(temp);

	temp = Button("3", 3, font, buttonShape);
	temp.setPosition(275, screen->getSize().y / 2);
	if (!unlocked[2])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	buttons.push_back(temp);
	
	temp = Button("4", 4, font, buttonShape);
	temp.setPosition(375, screen->getSize().y / 2);
	if (!unlocked[3])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	buttons.push_back(temp);

	temp = Button("5", 5, font, buttonShape);
	temp.setPosition(475, screen->getSize().y / 2);
	if (!unlocked[4])
		temp.setColor(locked);
	else
		temp.setColor(unlockedColor);
	buttons.push_back(temp);
	
}

void Menu::wonOptions()
{
	buttons.clear();
	screen->clear();

	Button temp("", 0, font);

	temp = Button("Next Level", 1, font);
	temp.setPosition(0, screen->getSize().y * .25);
	buttons.push_back(temp);

	temp = Button("Main Menu", 2, font);
	temp.setPosition(0, screen->getSize().y / 2);
	buttons.push_back(temp);

	temp = Button("Quit", 3, font);
	temp.setPosition(0, screen->getSize().y * .75);
	buttons.push_back(temp);

}

void Menu::lostOptions()
{
	buttons.clear();
	screen->clear();

	Button temp("", 0, font);

	temp = Button("Play Again", 1, font);
	temp.setPosition(0, screen->getSize().y * .25);
	buttons.push_back(temp);

	temp = Button("Main Menu", 2, font);
	temp.setPosition(0, screen->getSize().y / 2);
	buttons.push_back(temp);

	temp = Button("Quit", 3, font);
	temp.setPosition(0, screen->getSize().y * .75);
	buttons.push_back(temp);
}

bool Menu::isUnlocked(int level)
{
	if (unlocked[level])
		return true;
	return false;
}

void Menu::unlockLevel(int level)
{
	unlocked[level] = true;
}