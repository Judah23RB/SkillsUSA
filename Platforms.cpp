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
	sf::Texture texture;
	const sf::Texture* consttext = &texture;
	if (!texture.loadFromFile("Sprites/Default.png"))
	{
		platform.setFillColor(sf::Color::Red);
	}
	platform.setTexture(consttext);
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

sf::RectangleShape Platforms::getPlatSprite()
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