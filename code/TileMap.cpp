#include "TileMap.h"


TileMap::TileMap(sf::Texture &texture)
{
	this->texture = texture;
	this->sprite.setTexture(texture);
	this->sprite.setPosition(0, 0);
	
	initTileMap();
	initTiles();
}


TileMap::~TileMap()
{
}

void TileMap::initTileMap()
{

	TiXmlDocument doc("res/map/danich4.tmx");
	doc.LoadFile();
	TiXmlElement *root = doc.RootElement();

	std::vector < std::string > lay;
	std::string temp_str;


	if (root != NULL)
	{
		TiXmlElement *layer = root->FirstChildElement("layer");
		while (layer)
		{
			TiXmlElement *data = layer->FirstChildElement("data");
			if (NULL != data)
			{
				temp_str = data->GetText();
				lay.push_back(temp_str);
			}
			layer = layer->NextSiblingElement("layer");
		}

	}

	for (int i = 0; i < 3; i++)
	{
		std::vector<int> v;
		std::string s = lay[i];

		auto ptr = s.c_str();
		char *endptr = nullptr;
		while (ptr != s.c_str() + s.size()) {
			auto value = strtol(ptr, &endptr, 10);
			if (ptr == endptr) {
				ptr++;
			}
			else {
				ptr = endptr;
				v.push_back(value);
			}
		}

		for (int j = 0; j < 100; j++)
			for (int k = 0; k < 100; k++)
			{
				int ind = j * 100 + k;
				tile_map[i][j][k] = v[ind];
			}
	}





}

void TileMap::initTiles()
{
	TiXmlDocument doc("res/map/danich5.tmx");
	doc.LoadFile();
	TiXmlElement *root = doc.RootElement();

	if (root != NULL)
	{
		TiXmlElement *objectgroup = root->FirstChildElement("objectgroup");
		TiXmlElement *object = objectgroup->FirstChildElement("object");
		while (object)
		{
			if (NULL != object)
			{
				std::string w, h, x, y;
				sf::Vector2f pos, size;

				w = object->Attribute("width");
				h = object->Attribute("height");
				x = object->Attribute("x");
				y = object->Attribute("y");
				
				pos.x = atoi(x.c_str());
				pos.y = atoi(y.c_str());
				size.x = atoi(w.c_str());
				size.y = atoi(h.c_str());

				Tile tile(true,pos,size);

				tiles.push_back(tile);


			}
			object = object->NextSiblingElement("object");
		}
	}


	
}

std::vector<Tile> TileMap::getTiles()
{
	return this->tiles;
}


void TileMap::update(const float & dt, sf::Vector2f pos)
{
	sf::Vector2f start_pos;

	start_pos.x = pos.x / 2 ;
	start_pos.y = pos.y / 2;

	start_tileX = start_pos.x / 32 - 10;
	start_tileY = start_pos.y / 32 - 10;

	if (start_tileX < 0) start_tileX = 0;
	if (start_tileY < 0) start_tileY = 0;

	end_tileX = pos.x + start_pos.x + 200;
	end_tileY = pos.y + start_pos.y;
	
	end_tileX = end_tileX / 32 + 10;
	end_tileY = end_tileY / 32 + 10;

	if (end_tileX > 100) end_tileX = 100;
	if (end_tileY > 100) end_tileY = 100;
}

void TileMap::render(sf::RenderTarget * target)
{

	
	for (int layer = 0; layer < 3; layer++)
		for (int i = start_tileY; i < end_tileY; i++)
			for (int j = start_tileX; j < end_tileX; j++)
			{
			
				if (this->tile_map[layer][i][j] != 0)
				{
					int row, column;
					int temp = tile_map[layer][i][j];
					if (temp > 17)
					{
						row = (temp-1) / 17 ;
						column = (temp-1) - row * 17  ;
						this->sprite.setTextureRect(sf::IntRect((column) * 32, row*32 , 32, 32));
						this->sprite.setPosition(j * 32, i * 32);
	

					}
					else
					{
						this->sprite.setTextureRect(sf::IntRect((temp-1)*32, 0, 32, 32));
						this->sprite.setPosition(j * 32, i * 32);
					
					}

						target->draw(this->sprite);
				}
			}

	



}
