#include "Item.h"


Item::Item()
{
	this->id = -1;
}


Item::Item(int id)
{
	this->id = id;
}

Item::~Item()
{
}

sf::Vector2f Item::getPos()
{
	return pos;
}

void Item::setPos(sf::Vector2f pos)
{
	this->pos = pos;
}
