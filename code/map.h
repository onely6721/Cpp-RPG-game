#pragma once

#include <SFML\Graphics.hpp>



class Map
{
public:

	Map();
	~Map();
	
	void drawMap(sf::RenderWindow *window);
	
	const int m_height = 25;
	const int m_width = 40;

	sf::String TileMap[25] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0   t                k                 0",
	"0     t              k                 0",
	"0                                      0",
	"0         t           k                0",
	"0                                      0",
	"0                                      0",
	"0                   t                  0",
	"0                                      0",
	"0             t                        0",
	"0                                      0",
	"0                     k                0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
	};

protected:
	sf::Image m_i_map;
	sf::Texture m_t_map;
	sf::Sprite m_s_map;
	
};
