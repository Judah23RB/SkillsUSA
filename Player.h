#pragma once
#include <SFML/Graphics.hpp>

enum animState {idle = 0, left, right, falling};

class Player
{
public:
	Player();
	~Player();
	sf::Vector2f getPosition();
	sf::Sprite& getPlaySprite();
	sf::FloatRect getPlayerBounds();
	void setTexture(sf::Texture*);

	
	//physics
	void horizMoveModifier(double);
	void moveInput(bool, double); //fallstate, scroll speed
	void move(const int, const int);
	void updatePhysics();
	void setPosition(sf::Vector2f);
	void resetYVelocity(); // collision
	void collide(double);
	
	//Animations
	void updateAnimations();

	//health
	int getHealth();
	void updateHealth(int);//-1 damage, +1 health item
	void setHealth(int); //used to reset at start of level
private:
	//Physics
	sf::Vector2f velocity;
	float accel, drag, maxVelocity, maxfallVelocity, minVelocity, gravity, yMaxVelocity;
	double lMoveSpeed = -1;
	double rMoveSpeed = 1;
	
	//animation
	int currentState = animState::idle;
	sf::IntRect currentFrame;



	bool falling;
	double scrollSpeed;
	
	sf::Sprite sprite;
	int health = 3;
	
	void initPlayer();
	void initPhysics();
};

