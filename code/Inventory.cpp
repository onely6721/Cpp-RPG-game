#include "Inventory.h"



Inventory::Inventory(Mode &mode)
	:mode(mode)
{

	this->t_items.loadFromFile("res/img/invent/item.png");
	this->s_items.setTexture(t_items);

	this->t_inventory.loadFromFile("res/img/invent/Inventory1.png");
	this->s_inventory.setTexture(t_inventory);

	this->t_equip.loadFromFile("res/img/invent/Equipment.png");
	this->s_equip.setTexture(t_equip);

	sf::Vector2f size(1280,720);
	this->background.setSize(size);
	this->background.setFillColor(sf::Color(0, 0, 0, 230));

	size.x = 32;
	size.y = 32;

	this->exit.setSize(size);
	this->exit.setFillColor(sf::Color::Red);
	
	items.resize(54);
	initItems();

}


Inventory::~Inventory()
{
}

void Inventory::initItems()
{
	for (int i = 0; i < 54; i++)
	{
		Item item(-1);
		items[i] = item;
	}
}

void Inventory::addItem(Item item)
{
	for (int i = 0; i < 54; i++)
	{
		if (items[i].getId() == -1)
		{
			items[i] = item;
			break;
		} 
	}

}

void Inventory::update(sf::Vector2f pos, sf::Vector2f mouse_pos)
{
	this->s_inventory.setPosition(pos.x-640+275, pos.y-360+45);
	this->background.setPosition(pos.x - 640, pos.y -360);
	this->exit.setPosition(pos.x + 10 + 275, pos.y - 360 + 45);
	this->s_equip.setPosition(pos.x+380, pos.y - 240);


	mouse_pos.x += pos.x - 640;
	mouse_pos.y += pos.y - 360;
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (exit.getGlobalBounds().contains(mouse_pos))
		{
			mode = check;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		mode = check;
	}
	

}

void Inventory::render(sf::RenderTarget * target)
{
	target->draw(this->background);
	target->draw(this->s_inventory);
	target->draw(this->s_equip);
	for (int i = 0; i < 54; i++)
	{
		int id = items[i].getId();
		if (id != -1)
		{
			int r_item, r_inventory;
			int c_item, c_inventory;
			float pos_x, pos_y;
			r_item = int(id / 10);
			if (r_item > 0)
				c_item = id   - r_item * 10;
			else
				c_item = id;

			r_inventory = int(i  / 9);
			if (r_inventory > 0)
				c_inventory = i  - r_inventory * 9;
			else
				c_inventory = i ;

			pos_x = s_inventory.getPosition().x  + 25 + c_inventory* 71;
			pos_y = s_inventory.getPosition().y + 114 + r_inventory * 70;

			s_items.setTextureRect(sf::IntRect(c_item *52, r_item*50,52,50));
			s_items.setPosition(pos_x, pos_y);
			target->draw(s_items);

		}
	}

}
