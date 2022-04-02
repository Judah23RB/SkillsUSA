#include "Item.h"


Item::Item()
{

}

Item::~Item()
{

}

void Item::setPos(int x, int y)
{
	sprite.setPosition(x, y);
}

void Item::setTexture(const sf::Texture* text)
{
	sf::Texture texture = *text;
	sprite.setTexture(texture);
}

void Item::setTexture(sf::Texture* text)
{
	sprite.setTexture(*text);
}

void Item::setTextureRect(const sf::IntRect rect)
{
	sprite.setTextureRect(rect);
}

void Item::setType(int inp)
{
	type = inp;
}

sf::FloatRect Item::getBounds()
{
	return sprite.getGlobalBounds();
}

sf::Sprite& Item::getSprite()
{
	return sprite;
}

int Item::getType()
{
	return type;
}


void Item::clearSprite()
{
	sprite.setPosition(2000, 2000); //removes sprite from the screen
}

void Item::scroll(double speed)
{
	sprite.move(0, speed);
}