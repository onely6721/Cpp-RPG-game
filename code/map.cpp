#pragma once

#include "map.h"

Map::Map()
{
	
	m_i_map.loadFromFile("res/img/tileset.png");;
	m_t_map.loadFromImage(m_i_map);	
	m_s_map.setTexture(m_t_map);
	
}

Map::~Map()
{
}

void Map::drawMap(sf::RenderWindow *window)
{
	for (int i = 0; i < m_height; i++)
		for (int j = 0; j < m_width; j++)
		{
			if (TileMap[i][j] == ' ') m_s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == '0') m_s_map.setTextureRect(sf::IntRect(160, 0, 32, 32));
			if (TileMap[i][j] == 't') m_s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));

			m_s_map.setPosition(j * 32, i * 32);
			window->draw(m_s_map);

		}
}
