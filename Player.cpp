#include "Player.h"

Player::Player()
{
	initPlayer();
}

Player::~Player()
{

}

void Player::initPlayer()
{
	sprite.setSize(sf::Vector2f(30, 30));
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
	sprite.setFillColor(sf::Color::Blue);
	sprite.setPosition(300,10);
}

const sf::RectangleShape& Player::getPlaySprite() const
{
	return sprite;
}

sf::FloatRect Player::getPlayerBounds()
{
	return sprite.getGlobalBounds();
}
sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

void Player::moveLeft(int dist)
{
	sprite.move(-dist, 0);
}

void Player::moveRight(int dist)
{
	sprite.move(dist, 0);
}

void Player::fall()
{
	sprite.move(0, .1);
}

void Player::setPosition(sf::Vector2f inp)
{
	sprite.setPosition(inp.x, inp.y);
}

void Player::collide(double scroll)
{
	sprite.move(0, scroll);
}

int Player::getHealth()
{
	return health;
}

void Player::updateHealth(int inp)
{
	health += inp;
}

void Player::setHealth(int inp)
{
	health = inp;
}

