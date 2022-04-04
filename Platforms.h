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
	sf::RectangleShape& getPlatSprite();
	
	void scroll(double);

private:
	sf::RectangleShape platform;
	int type; //1 is basic, 2 is fake, 3 moves left, 4 moves right, 5 is spikes, 6 is end
	
	void initplat();
};