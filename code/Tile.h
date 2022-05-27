#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
public:

	Tile(bool collision, sf::Vector2f pos, sf::Vector2f size);
	virtual ~Tile();

	bool getCollision();
	sf::RectangleShape getRect();
	sf::Vector2f getPositon();
	sf::Vector2f getSize();

	void render(sf::RenderTarget *target);

private:
	
	sf::RectangleShape rect;
	bool collision;

};

