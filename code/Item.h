#pragma once
#include <SFML/Graphics.hpp>

class Item
{
public:
	Item();
	Item(int id);
	virtual ~Item();

	int getId() { return this->id; };
	sf::Vector2f getPos();
	
	void setPos(sf::Vector2f pos);

private: 
	sf::Vector2f pos;
	int id;
	int count;



};

