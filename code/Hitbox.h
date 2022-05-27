#pragma once
#include<SFML/Graphics.hpp>

class Hitbox
{
public:
	Hitbox(sf::Vector2f size, sf::Vector2f pos,float ind_x = 0, float ind_y = 0);
	
	virtual ~Hitbox();

	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::FloatRect getGlobalBounds();
	sf::RectangleShape *getRect();

	bool checkCollision(sf::RectangleShape tile_rect);
	void rotate(float angle);
	

	void update(sf::Vector2f pos);
	void render(sf::RenderTarget *target);

private:

	float ind_x, ind_y;
	sf::RectangleShape *rect;

};

