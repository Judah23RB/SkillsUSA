#pragma once
#include <SFML/Graphics.hpp>

enum animState {idle = 0, left, right, falling};

class Player
{
public:
	Player();
	~Player();
	sf::Vector2f getPosition();
	sf::RectangleShape& getPlaySprite();
	sf::FloatRect getPlayerBounds();
	
	//physics
	void moveInput(bool, double); //fallstate, scroll speed
	void move(const int, const int);
	void updatePhysics();
	void setPosition(sf::Vector2f);
	void resetYVelocity(); // collision
	void collide(double);
	
	//Animations
	const bool& getAnimationState();
	void resetAnimationTimer();
	void updateAnimations();

	//health
	int getHealth();
	void updateHealth(int);//-1 damage, +1 health item
	void setHealth(int); //used to reset at start of level
private:
	//Physics
	sf::Vector2f velocity;
	float accel, drag, maxVelocity, maxfallVelocity, minVelocity, gravity, yMaxVelocity;
	
	//animation
	int currentState;
	sf::Clock animationTimer;
	sf::IntRect currentFrame;
	bool animationSwitch;

	bool falling;
	double scrollSpeed;
	
	sf::RectangleShape sprite;
	int health = 3;
	
	void initPlayer();
	void initPhysics();
};

