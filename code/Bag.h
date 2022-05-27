#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Bag
{
public:
	Bag(sf::Vector2f pos, std::vector<int> &&id_items);
	~Bag();

	std::vector<int>& getIdItems();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();

	void update(sf::Vector2i mouse_pos);
	void render(sf::RenderTarget *target);

private:
	std::vector<int> id_items;

	bool active;
	sf::Texture t_bag;
	sf::Sprite s_bag;
	sf::Vector2f pos;


};

