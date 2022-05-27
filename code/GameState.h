#pragma once
#include <iostream>
#include <sqlite3.h>
#include <utility>

#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include "MainMenuState.h"
#include "Tile.h"
#include "Hud.h"
#include "blacout.h"
#include "Inventory.h"
#include "Item.h"
#include "Bag.h"
#include <thread>

class GameState :
	public State
{
public:
	GameState(sf::RenderWindow *window, std::stack<State*> *states);
	virtual ~GameState();

	void PlayerAttack();
	void getLoot(std::vector<int> &id_items);

	void initTextures();
	void initPlayer();
	void initTileMap();
	void initView();
	void initTiles();
	void initEnemy();
	void initHud();
	void initMusic();
	void initInventory();

	void initBlackout();
	
	void getRange();

	void renderEnemy();
	void collisions();

	void updateEnemy(const float &dt);
	void updateCollisionsEnemy();
	void updateCollisions(const float&dt);
	void updateTileMap(const float &dt);
	void updateView();
	void updatePlayer(const float &dt);
	void updateInput(const float &dt);
	void updateMouseInput(const float &dt);
	void updateHud();
	void updateCursor();
	void updateMusic();
	void updateBlackout();
	void updateBag(sf::Vector2i mouse_pos);
	
	
	void renderBags();
	void renderHud();
	void renderBlackout();

	void update(const float& dt);
	void render(sf::RenderTarget *target);


private:
	sqlite3 *db = 0;

	sf::Sprite cursor;
	sf::Music music;

	std::map<std::string, sf::Texture> textures;
	std::vector<Tile> tiles;
	std::vector<Enemy*> enemies;
	std::vector<Bag*> bags;

	std::thread *collision;

	sf::View view;

	Mode mode;

	Blackout *blackout;
	Inventory *inventory;
	TileMap *t_map;
	Hud *hud;
	Player *player;

};

