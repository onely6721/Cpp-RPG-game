#include "Tile.h"



Tile::Tile(bool collision, sf::Vector2f pos, sf::Vector2f size)
{
	this->collision = collision;
	rect.setSize(size);
	rect.setPosition(pos);
	this->rect.setOutlineColor(sf::Color(255, 0, 0));
	this->rect.setOutlineThickness(1);
	this->rect.setFillColor(sf::Color::Transparent);
}


Tile::~Tile()
{
}


bool Tile::getCollision()
{
	return this->collision;
}

sf::RectangleShape Tile::getRect()
{
	return this->rect;
}

sf::Vector2f Tile::getPositon()
{
	return rect.getPosition();
}

sf::Vector2f Tile::getSize()
{
	return rect.getSize();
}

void Tile::render(sf::RenderTarget *target)
{
	target->draw(rect);
}

