#include "Hitbox.h"



Hitbox::Hitbox(sf::Vector2f size, sf::Vector2f pos, float ind_x, float ind_y)
{
	this->ind_x = ind_x;
	this->ind_y = ind_y;

	this->rect = new sf::RectangleShape();
	this->rect->setSize(size);
	this->rect->setOutlineColor(sf::Color(255, 0, 0));
	this->rect->setOutlineThickness(2);
	this->rect->setFillColor(sf::Color::Transparent);
	this->rect->setPosition(pos.x + ind_x, pos.y + ind_y);
}


Hitbox::~Hitbox()
{
}

sf::Vector2f Hitbox::getPosition()
{
	return this->rect->getPosition();
}

sf::Vector2f Hitbox::getSize()
{
	return this->rect->getPosition();
}

sf::FloatRect Hitbox::getGlobalBounds()
{
	return rect->getGlobalBounds();
}

sf::RectangleShape *Hitbox::getRect()
{
	return this->rect;
;
}

bool Hitbox::checkCollision(sf::RectangleShape tile_rect)
{
	if (this->rect->getGlobalBounds().intersects(tile_rect.getGlobalBounds()))
		return true;
	else
		return false;
}

void Hitbox::rotate(float angle)
{
	this->rect->rotate(angle);
}

void Hitbox::update(sf::Vector2f pos)
{
	this->rect->setPosition(pos.x + this->ind_x, pos.y + this->ind_y);
}

void Hitbox::render(sf::RenderTarget * target)
{
	target->draw(*this->rect);
}
