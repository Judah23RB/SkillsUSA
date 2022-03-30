#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:
	Player();
	~Player();
	sf::Vector2f getPosition();
	const sf::RectangleShape& getPlaySprite() const;
	sf::FloatRect getPlayerBounds();
	void moveLeft(int);
	void moveRight(int);
	void fall();
	void setPosition(sf::Vector2f);
	void collide(double);
	int getHealth();
	void updateHealth(int);//-1 damage, +1 health item
	void setHealth(int); //used to reset at start of level
private:
	sf::RectangleShape sprite;
	int health = 3;
	void initPlayer();
};

