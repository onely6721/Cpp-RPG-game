#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

enum direction {up=0,down, left ,right};

class Movement
{
public:

	Movement(sf::Sprite &sprite, float speed);
	~Movement();
	
	void setDirection(direction dir);


	void move(const float &dt);
	void update(const float &dt); 

	sf::Vector2f getVelocity();
	
	bool getMov() { return moving; }
	void setMov(bool moving) { this->moving = moving; }



private:

	bool moving;
	direction dir;

	sf::Sprite &sprite;
	sf::Vector2f velocity;
	float speed;
	
};

