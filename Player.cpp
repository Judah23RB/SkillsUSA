#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player()
{
	initPlayer();
}

Player::~Player()
{

}

void Player::initPlayer()
{
	sprite.setScale(1.5, 1.5);
	sprite.setPosition(300,10);
	currentState = animState::idle;
	initPhysics();
}

void Player::initPhysics()
{
	maxVelocity = 1;
	maxfallVelocity = .6;
	minVelocity = .05;
	accel = 1.1;
	drag = 0.8;
	gravity = .1;
	yMaxVelocity = .5;
}

sf::Sprite& Player::getPlaySprite()
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

	currentState = animState::idle;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (getPosition().x > 0)
			move(lMoveSpeed, 0);
		currentState = animState::left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (getPosition().x < 600)
			move(rMoveSpeed, 0);
		currentState = animState::right;
	}
	updateAnimations();
	updatePhysics();
}


//allows tread platform to impact player movement speed;
void Player::horizMoveModifier(double modifier)
{
	//increases and decreases opposite movement speed with same math
	rMoveSpeed += modifier;
	lMoveSpeed += modifier;
	maxVelocity += abs(modifier * 1.5);

	//reset movement speeds
	if (modifier == 0)
	{
		maxVelocity = 1;
		rMoveSpeed = 1;
		lMoveSpeed = -1;
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

void Player::updateAnimations()
{
	if (currentState == idle)
	{
		currentFrame = sf::IntRect(0, 0, 18, 22);
		sprite.setTextureRect(currentFrame);
	}
	if (currentState == right)
	{
		currentFrame = sf::IntRect(94, 0, 18, 22);
		sprite.setTextureRect(currentFrame);
	}
	if (currentState == left)
	{
		currentFrame = sf::IntRect(19, 0, 20, 22);
		sprite.setTextureRect(currentFrame);
	}
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



void Player::setTexture(sf::Texture* text)
{
	sprite.setTexture(*text);
	currentFrame = sf::IntRect(0, 0, 18, 22);
	sprite.setTextureRect(currentFrame);
}




