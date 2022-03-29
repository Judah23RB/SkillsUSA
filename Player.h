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
private:
	sf::RectangleShape sprite;
	void initPlayer();
};

