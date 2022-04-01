#pragma once
#include <SFML/Graphics.hpp>

class Item
{
public:
	Item();
	~Item();
	
	void setType(int);
	void setPos(int, int);
	void setTexture(const sf::Texture*);
	void setTextureRect(const sf::IntRect);
	
	sf::FloatRect getBounds();
	sf::Sprite& getSprite();
	int getType();

	void clearSprite();

	void scroll(double);

private:
	int type = 0; //1 is health, 2 is slow, 3 is score
	sf::Sprite sprite;




};

