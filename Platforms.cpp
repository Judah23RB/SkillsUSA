#include "Platforms.h"


Platforms::Platforms()
{
	initplat();
}

Platforms::~Platforms()
{

}

void Platforms::initplat()
{
	platform.setOrigin(platform.getSize().x / 2, platform.getSize().y / 2);
}

void Platforms::setPos(sf::Vector2f coords)
{
	platform.setPosition(coords);
}

void Platforms::setPos(int x, int y)
{
	platform.setPosition(sf::Vector2f(x, y));
}

void Platforms::setSize(int length)
{
	platform.setSize(sf::Vector2f(length, 10));
}

sf::Vector2f Platforms::getPos()
{
	return platform.getPosition();
}

sf::FloatRect Platforms::getPlatBounds()
{
	return platform.getGlobalBounds();
}

sf::RectangleShape& Platforms::getPlatSprite()
{
	return platform;
}

void Platforms::scroll(double speed)
{
	platform.move(0, speed);
}



void Platforms::setTexture(const sf::Texture* textr)
{
	platform.setTexture(textr);
}

void Platforms::setTextureRect(const sf::IntRect rect)
{
	platform.setTextureRect(rect);
}
//1 is basic, 2 is fake, 3 is moving, 4 is end
void Platforms::setType(int inp)
{
	type = inp;
}

int Platforms::getType()
{
	return type;
}