#include "Bag.h"



Bag::Bag(sf::Vector2f pos, std::vector<int> &&id_items)
	:id_items(id_items)
{
	this->t_bag.loadFromFile("res/img/invent/bag.png");
	this->s_bag.setTexture(t_bag);
	this->s_bag.setPosition(pos.x + 32, pos.y + 32);


}


Bag::~Bag()
{
}

std::vector<int>& Bag::getIdItems()
{
	return this->id_items;
}

sf::FloatRect Bag::getGlobalBounds()
{
	return this->s_bag.getGlobalBounds();
}

sf::Vector2f Bag::getPosition()
{
	return s_bag.getPosition();
}

void Bag::update(sf::Vector2i  mouse_pos)
{
	this->active = false;


	if (this->s_bag.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
		active = true;
	else
		active = false;

	if (active)
		s_bag.setColor(sf::Color(255, 127, 0));
	else
		s_bag.setColor(sf::Color::White);

	
	
}

void Bag::render(sf::RenderTarget * target)
{
	target->draw(this->s_bag);
}
