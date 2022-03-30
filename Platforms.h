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
	
	sf::Vector2f getPos();
	sf::FloatRect getPlatBounds();
	sf::RectangleShape getPlatSprite();
	
	void scroll(double);

private:
	sf::RectangleShape platform;
	void initplat();


};

