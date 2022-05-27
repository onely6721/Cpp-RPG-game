#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>
#include <map>
#include <string>
#include "tinyxml.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <random>
class TileMap
{
public:
	TileMap(sf::Texture &texture);
	virtual ~TileMap();

	void initTileMap();
	void initTiles();

	std::vector<Tile> getTiles();

	void update(const float &dt, sf::Vector2f pos);
	void render(sf::RenderTarget *target = nullptr);


private:
	
	int tile_map[3][100][100];


	

	std::vector<Tile> tiles;

	sf::Texture texture;
	sf::Sprite sprite;

	int start_tileX , end_tileX;
	int start_tileY,  end_tileY;

};

