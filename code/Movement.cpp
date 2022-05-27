#include "Movement.h"






Movement::Movement(sf::Sprite& sprite, float speed)
	:sprite(sprite), speed(speed)
{

	moving = true;
	dir = right;

	velocity.x = 10;
	velocity.y = 10;
}

Movement::~Movement()
{
}

void Movement::setDirection(direction dir)
{
	this->dir = dir;
}

void Movement::move(const float & dt)
{
	
	if (moving == false)
	{
		velocity.x = 0;
		velocity.y = 0;
	}
	else
	{
		switch (dir)
		{
			case up:
				velocity.y = -1.f;
				velocity.x = 0.f;
				break;
			case down:
				velocity.y = 1.f;
				velocity.x = 0.f;
				break;
			case right:
				velocity.y = 0.f;
				velocity.x = 1.f;
				break;
			case left:
				velocity.y = 0.f;
				velocity.x = -1.f;
				break;
		}
	}

	


}

void Movement::update(const float & dt)
{
	move(dt);
}

sf::Vector2f Movement::getVelocity()
{

	return velocity;
}



