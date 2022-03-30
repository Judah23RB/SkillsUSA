#include "Player.h"
#include <cmath>

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
	initPhysics();
}

void Player::initPhysics()
{
	maxVelocity = 1;
	maxfallVelocity = .5;
	minVelocity = .05;
	accel = 1.1;
	drag = 0.8;
	gravity = .1;
	yMaxVelocity = .5;
}

sf::RectangleShape& Player::getPlaySprite()
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


void Player::moveInput(bool fallState, double scroll)
{
	falling = fallState;
	scrollSpeed = scroll;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (getPosition().x > 0)
			move(-1, 0);
		
		updatePhysics();

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (getPosition().x < 600)
			move(1, 0);
		
		updatePhysics();
	}
}
void Player::move(const int x, const int y)
{
	//acceleration
	velocity.x += (x * accel);
	if (!falling)
	{
		if (abs(velocity.x) > maxVelocity)
		{
			if (velocity.x < 0)
				velocity.x = -1 * maxVelocity;
			else
				velocity.x = maxVelocity;
		}
	}
	else
	{
		if (abs(velocity.x) > maxfallVelocity)
		{
			if (velocity.x < 0)
				velocity.x = -1 * maxfallVelocity;
			else
				velocity.x = maxfallVelocity;
		}
		sprite.move(0, scrollSpeed);
	}

}

//bool ensures gravity doesnt work twice, as movement is handled in game
void Player::updatePhysics()
{
	if (velocity.y != -1)
	{
		//Gravity
		velocity.y += 1.0 + gravity;

		if (velocity.y > yMaxVelocity)
			velocity.y = yMaxVelocity;
	}



	//decceleartion
	velocity.x = velocity.x * drag;
	velocity.y = velocity.y * drag;

	if (abs(velocity.x) < minVelocity)
		velocity.x = 0;

	if (abs(velocity.y) < minVelocity)
		velocity.y = 0;

	sprite.move(velocity);
	
		
}


void Player::resetYVelocity()
{
	velocity.y = -1;
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




