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
	
	void moveInput(bool, double); //fallstate, scroll speed
	
	void fall();
	void move(const int, const int);
	void updatePhysics();
	void setPosition(sf::Vector2f);
	void resetYVelocity(); // collision
	void collide(double);
	
	int getHealth();
	void updateHealth(int);//-1 damage, +1 health item
	void setHealth(int); //used to reset at start of level
private:
	//Physics
	sf::Vector2f velocity;
	float accel;
	float drag;
	float maxVelocity;
	float maxfallVelocity; //limit horizontel movement when falling
	float minVelocity;
	float gravity;
	float yMaxVelocity;

	bool falling;
	double scrollSpeed;
	
	sf::RectangleShape sprite;
	int health = 3;
	void initPlayer();
	void initPhysics();
};

