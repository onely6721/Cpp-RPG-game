#include "GameState.h"



GameState::GameState(sf::RenderWindow *window, std::stack<State*> *states)
	:State(window, states), mode(game)
{
	sqlite3_open("res/db/dungeonhunter.db", &this->db);


	initView();
	initPlayer();
	initTextures();
	initTileMap();
	initTiles();
	initEnemy();
	initHud();
	initMusic();
	initInventory();
	initBlackout();


}


GameState::~GameState()
{
	sqlite3_close(this->db);
}

void GameState::PlayerAttack()
{
	sf::Vector2f pos_sprite = this->player->getPos();
	sf::Vector2i pos_mouse = sf::Mouse::getPosition(*this->window);
	pos_mouse.x += this->view.getCenter().x - 640;
	pos_mouse.y += this->view.getCenter().y - 360;



	sf::Vector2f path_dir;
	sf::Vector2f path(pos_mouse.x - 35, pos_mouse.y - 50);

	if (pos_mouse.x < this->player->getPos().x + 35)
	{
		path_dir.x = -1;
	}
	else
	{
		path_dir.x = 1;
	}
	if (pos_mouse.y < this->player->getPos().y + 50)
	{
		path_dir.y = -1;
	}
	else
	{
		path_dir.y = 1;
	}

	if (abs(path.x - this->player->getPos().x) < 48)
	{
		path.x = this->player->getPos().x;
		path_dir.x = 0;
	}
	if (abs(path.y - this->player->getPos().y) < 48)
	{
		path.y = this->player->getPos().y;
		path_dir.y = 0;
	}

	if (abs(path.x - this->player->getPos().x) > 48 || abs(path.y - this->player->getPos().y) > 48)
	{
		this->player->setPath(path);
		this->player->setPathDir(path_dir);
		this->player->setRun(true);
	}
}

void GameState::getLoot(std::vector<int> &id_items)
{
	sqlite3_stmt    *res;
	std::string sql;
	for (auto at = id_items.begin(); at != id_items.end(); at++)
	{
		this->inventory->addItem(*at);

	    sql = "INSERT INTO Inventory VALUES (1," + std::to_string(*at) + ");";
		
		sqlite3_prepare_v2(this->db, sql.c_str(), 1000, &res, NULL);
		sqlite3_step(res);

	}
}

void GameState::initTextures()
{
	sf::Texture *temp;
	temp = new sf::Texture();

	temp->loadFromFile("res/img/tiles/danich3.png");
	textures.insert(std::pair<std::string, sf::Texture>("tilemap", *temp));
	temp->loadFromFile("res/img/bar2.png");
	textures.insert(std::pair<std::string, sf::Texture>("bar", *temp));
	temp->loadFromFile("res/img/spell.png");
	textures.insert(std::pair<std::string, sf::Texture>("spell", *temp));
	temp->loadFromFile("res/img/cursor.png");
	textures.insert(std::pair<std::string, sf::Texture>("cursor", *temp));
	this->cursor.setTexture(textures["cursor"]);
	temp->loadFromFile("res/img/mana.png");
	textures.insert(std::pair<std::string, sf::Texture>("mana", *temp));
	temp->loadFromFile("res/img/hp.png");
	textures.insert(std::pair<std::string, sf::Texture>("hp", *temp));
	temp->loadFromFile("res/img/Healthbar.png");
	textures.insert(std::pair<std::string, sf::Texture>("hp_bar_enemy", *temp));
	temp->loadFromFile("res/img/gui/inventory.png");
	textures.insert(std::pair<std::string, sf::Texture>("inv", *temp));
	temp->loadFromFile("res/img/gui/door.png");
	textures.insert(std::pair<std::string, sf::Texture>("door", *temp));
	temp->loadFromFile("res/img/gui/gift.png");
	textures.insert(std::pair<std::string, sf::Texture>("gift", *temp));

	this->window->setMouseCursorVisible(false);
}

void GameState::initPlayer()
{
	sqlite3_stmt    *res;
	const char      *tail;
	sqlite3_prepare_v2(this->db, "SELECT lvl,pos_x,pos_y FROM Player WHERE id_player = 1", 1000, &res, &tail);
	int t_lvl = 0, t_x = 0, t_y = 0;
	while (sqlite3_step(res) == SQLITE_ROW)
	{
		t_lvl = int(sqlite3_column_int(res, 0));
		t_x = int(sqlite3_column_int(res, 1));
		t_y = int(sqlite3_column_int(res, 2));
	}



	this->player = new Player(t_lvl,t_x,t_y);
}

void GameState::initTileMap()
{
	this->t_map = new TileMap(textures["tilemap"]);
}

void GameState::initView()
{

	view.reset(sf::FloatRect(0, 0, 1280, 720));
}

void GameState::initTiles()
{
	this->tiles = t_map->getTiles();

	
}

void GameState::initEnemy()
{
	sf::Vector2f temp_pos(1800, 1800);
	this->enemies.push_back(new Enemy(temp_pos, textures["hp_bar_enemy"]));
	temp_pos.x = 1500;
	temp_pos.y = 1800;
	this->enemies.push_back(new Enemy(temp_pos, textures["hp_bar_enemy"]));
	temp_pos.x = 1500;
	temp_pos.y = 1900;
	this->enemies.push_back(new Enemy(temp_pos, textures["hp_bar_enemy"]));
}

void GameState::initHud()
{
	this->hud = new Hud(this->player,this->textures["bar"],
		this->textures["spell"], this->textures["mana"], this->textures["hp"],
		this->textures["door"], this->textures["inv"], this->textures["gift"]);
}

void GameState::initMusic()
{
	music.openFromFile("res/sound/TownTheme.ogg");
	music.setVolume(10);
	music.setAttenuation(10);
	music.setLoop(true);
}

void GameState::initInventory()
{

	inventory = new Inventory(this->mode);

	sqlite3_stmt    *res;
	const char      *tail;
	sqlite3_prepare_v2(this->db, "SELECT id_item FROM Inventory WHERE id_player = 1", 1000, &res, &tail);
	
	while (sqlite3_step(res) == SQLITE_ROW)
	{
		int id = sqlite3_column_int(res, 0);
		Item item(id);
		inventory->addItem(item);
	}


}

void GameState::initBlackout()
{
	this->blackout = new Blackout();
}

void GameState::getRange()
{
	
}

void GameState::renderEnemy()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i] != nullptr)
			enemies[i]->render(this->window);
	}

}

void GameState::collisions()
{
	updateCollisionsEnemy();
}



void GameState::updateEnemy(const float & dt)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i] != nullptr)
			enemies[i]->update(dt);
	}

}

void GameState::updateCollisionsEnemy()
{
	std::vector<Shell*> &arrows = this->player->getShell();
	


	for (int i = 0; i < arrows.size(); i++)
		for (int j = 0; j < enemies.size(); j++)
		{
			if (arrows[i] != nullptr && enemies[j] != nullptr)
			{
				sf::FloatRect rect_arrow =	arrows[i]->getRect()->getGlobalBounds();
				sf::FloatRect rect_enemy = enemies[j]->getRect()->getGlobalBounds();

				if (rect_arrow.intersects(rect_enemy))
				{

					delete arrows[i];
					arrows[i] = nullptr;
					if (enemies[j] != nullptr)
					{
						enemies[j]->setTarget(this->player);
						enemies[j]->getDmg(600);
						if (enemies[j]->getHp() <= 0)
						{
							sf::Vector2f *temp = new sf::Vector2f();
							*temp = enemies[j]->getPos();
							std::vector<int> items;
							items.push_back(29);
							items.push_back(30);
							bags.push_back(new Bag(*temp,std::move(items)));
							enemies[j] = nullptr;
							delete enemies[j];
							delete temp;
							this->player->setTarget(nullptr);
						}
					}
					
				}
			}

		}


}

void GameState::updateCollisions(const float &dt)
{
	for (int i = 0; i < tiles.size() ; i++)
	{
		if (this->player->checkCollisonBody(tiles[i].getRect()))
	
		{
			int dir = player->getDir();

			sf::Vector2f velocity(0, 0);

			if (dir == 0)
			{
				this->player->move(dt,0, 1);
		
				this->player->setRun(false);
				this->player->setVelocity(velocity);
			}
			else if (dir == 1)
			{
				this->player->move(dt,0, -1);
			
				this->player->setRun(false);
				this->player->setVelocity(velocity);
			}
			else  if (dir == 2)
			{
				this->player->move(dt,1, 0);
				this->player->setAttack(false);
				this->player->setRun(false);
				this->player->setVelocity(velocity);
			}

			else if (dir == 3)
			{
				this->player->move(dt,-1, 0);
						
				this->player->setRun(false);
				this->player->setVelocity(velocity);
			}
			
		}
		updateCollisionsEnemy();
	}
	

}

void GameState::updateTileMap(const float &dt)
{
	this->t_map->update(dt,view.getCenter());
}

void GameState::updateView()
{
	sf::Vector2f temp = player->getPos();
	
	if (temp.x < 640) { temp.x = 640; }
	if (temp.y < 360) { temp.y = 360; }
	if (temp.x > 2320) { temp.x = 2320; }
	if (temp.y > 3240) { temp.y = 3240; }

	this->view.setCenter(temp);
	this->window->setView(this->view);
}

void GameState::updatePlayer(const float & dt)
{
	this->player->update(dt);
	if (this->player->getCurrentHp() <= 0)
	{

		sf::Vector2f temp(1600, 2700);
		this->player->setPosition(temp);
		this->player->setHp(100);
	}
}

void GameState::updateInput(const float &dt)
{
}

void GameState::updateMouseInput(const float & dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bool loot = false , attack = false;
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(*this->window);

		mouse_pos.x += view.getCenter().x - 640;
		mouse_pos.y += view.getCenter().y - 360;

		for (auto at = bags.begin(); at != bags.end(); at++)
		{
			if (*at != nullptr)
			{
				sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window));
				mouse_pos.x += this->view.getCenter().x - float(640);
				mouse_pos.y += this->view.getCenter().y - float(360);

				sf::Vector2f temp_pos;
			    temp_pos.x = abs(this->player->getPos().x - mouse_pos.x);
				temp_pos.y = abs(this->player->getPos().y - mouse_pos.y);

				float len = sqrt(temp_pos.x * temp_pos.x +  temp_pos.y * temp_pos.y);

				if ((*at)->getGlobalBounds().contains(mouse_pos) && len < 200)
				{
					loot = true;
					this->getLoot((*at)->getIdItems());
					(*at) = nullptr;
					delete *at;
				}
			}
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i] != nullptr)
			{
				sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window));
				mouse_pos.x += this->view.getCenter().x - float(640);
				mouse_pos.y += this->view.getCenter().y - float(360);
				if (enemies[i]->getGlobalBounds().contains(mouse_pos))
				{
					this->player->setTarget(enemies[i]);
					attack = true;
				} 
				
			}

		}

		
		if (this->hud->invGetBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
		{
		
			mode = inv;
		} 
		else if (!loot)
		{
			this->player->setAttack(attack);
			this->PlayerAttack();
		}

	}
}

void GameState::updateHud()
{
	this->hud->update(this->view.getCenter());
}

void GameState::updateCursor()
{
	sf::Vector2i pos_mouse = sf::Mouse::getPosition(*this->window);
	pos_mouse.x += this->view.getCenter().x - 640;
	pos_mouse.y += this->view.getCenter().y - 360;
	this->cursor.setPosition(pos_mouse.x, pos_mouse.y);
}

void GameState::updateMusic()
{
	if (this->music.getStatus() != sf::Music::Playing)
	{
		this->music.play();
	
	}
}

void GameState::updateBlackout()
{
	this->blackout->update(view.getCenter());
}

void GameState::updateBag(sf::Vector2i mouse_pos)
{
	for (auto at = bags.begin(); at != bags.end(); at++)
	{
		if(*at != nullptr)
			(*at)->update(mouse_pos);
	}

}

void GameState::renderBags()
{
	for (auto at = bags.begin(); at != bags.end(); at++)
	{
		if(*at != nullptr)
			(*at)->render(this->window);
	}
}

void GameState::renderHud()
{
	this->hud->render(this->window);
}

void GameState::renderBlackout()
{
	this->blackout->render(this->window);
}

void GameState::update(const float &dt)
{
	sf::Vector2i pos_mouse = static_cast<sf::Vector2i>(this->cursor.getPosition());

	if (mode == game)
	{
	
		updateBag(pos_mouse);
		updateCollisions(dt);
		updateMouseInput(dt);
		updateInput(dt);
		updatePlayer(dt);
		updateTileMap(dt);
		updateView();
		updateEnemy(dt);
		updateHud();

	}
	if (mode == check)
	{
		this->mode = game;
	}

	if (mode == inv)
	{
		this->inventory->update(view.getCenter(),static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window)));
	}

	updateCursor();
	updateMusic();

	
}

void GameState::render(sf::RenderTarget *target = nullptr)
{
	
	if (mode == game)
	{
		this->t_map->render(this->window);
		renderBags();
		this->player->render(this->window);
		renderEnemy();
		renderHud();
	}
	//renderBlackout();
	if (mode == inv)
	{
		this->inventory->render(target);
	}
	this->window->draw(this->cursor);
	

}