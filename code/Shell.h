#pragma once
#include "Entity.h"


class Shell :
	public Entity
{
public:
	Shell(std::string path, float max_range, sf::Vector2f pos, sf::Vector2f dir_arrow, int dir_player,float speed);
	virtual ~Shell();

	void initHitbox(sf::Vector2f size, sf::Vector2f pos);

	sf::RectangleShape *getRect();

	bool checkCollision(sf::RectangleShape &shape);
	bool checkEndPoint();

	void updateHitbox();

	void update(const float &dt);
	void render(sf::RenderTarget *target);

	void move(const float dt, float dir_x, float dir_y) ;
	void setPosition(sf::Vector2f pos) ;


private:

	Hitbox *hitbox;
	
	sf::Vector2f dir;
	int dir_player;

	float speed;
	float max_range;
	float traveled_range;
	float range;



};

