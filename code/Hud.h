#pragma once

#include "Player.h"
#include <sstream>

class Hud
{
public:
	Hud(Player *player, sf::Texture &t_bar, sf::Texture &t_spell,
		sf::Texture &t_mana, sf::Texture &t_hp, sf::Texture &t_door,
		sf::Texture &t_inventory, sf::Texture &t_gift);
	virtual ~Hud();

	sf::FloatRect invGetBounds();

	void updateHp();
	void updatateMana();

	void update(sf::Vector2f view_pos);
	void render(sf::RenderTarget *target);



private:

	sf::Sprite bar;
	sf::Sprite spell;
	sf::Sprite hp;
	sf::Sprite mana;
	sf::Sprite door;
	sf::Sprite inventory;
	sf::Sprite gift;


	Player *player;

	sf::Text text_hp;
	sf::Text text_mana;
	sf::Text text_lvl;

	sf::Font font;
};

