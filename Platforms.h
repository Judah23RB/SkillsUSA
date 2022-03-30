#pragma once
#include <SFML/Graphics.hpp>

class Platforms
{
public:
	Platforms();
	~Platforms();
	void setTexture(const sf::Texture*);
	void setTextureRect(const sf::IntRect);
	void setPos(int, int);
	void setPos(sf::Vector2f);
	void setSize(int);
	void setType(int);
	int getType();
	
	sf::Vector2f getPos();
	sf::FloatRect getPlatBounds();
	sf::RectangleShape getPlatSprite();
	
	void scroll(double);
	void scroll_moving(double, double);

private:
	sf::RectangleShape platform;
	int type; //1 is basic, 2 is fake, 3 is moving
	double x_cord; //used for moving platform as origin point
	void initplat();


};

