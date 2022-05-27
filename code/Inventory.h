#pragma once


#include <SFML/Graphics.hpp>
#include <vector>
#include "Item.h"
#include <iostream>
#include <cmath>

enum Mode {
	game = 0,
	inv,
	menu,
	check
};

class Inventory
{
public:
	Inventory(Mode &mode);
	virtual ~Inventory();

	void initItems();


	void addItem(Item item);

	void update(sf::Vector2f pos, sf::Vector2f mouse_pos);
	void render(sf::RenderTarget *target);

private:

	std::vector<Item> items;
 
	sf::Texture t_items;
	sf::Sprite s_items;

	Mode &mode;

	sf::Texture t_equip;
	sf::Sprite s_equip;
	
	sf::Texture t_inventory;
	sf::Sprite s_inventory;

	sf::RectangleShape exit;
	sf::RectangleShape background;

};

