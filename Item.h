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
	
	sf::FloatRect getBounds();
	sf::Sprite& getSprite();

private:
	int type; //1 is health, 2 is slow, 3 is score
	sf::Sprite sprite;




};

