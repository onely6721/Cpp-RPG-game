#include "Hud.h"



Hud::Hud(Player *player, sf::Texture &t_bar, sf::Texture &t_spell, 
	sf::Texture  &t_mana, sf::Texture &t_hp, sf::Texture &t_door, 
	sf::Texture &t_inventory, sf::Texture &t_gift)
{
	this->player = player;
	this->bar.setTexture(t_bar);
	this->spell.setTexture(t_spell);
	this->hp.setTexture(t_hp);
	this->mana.setTexture(t_mana);
	this->door.setTexture(t_door);
	this->gift.setTexture(t_gift);
	this->inventory.setTexture(t_inventory);

	this->font.loadFromFile("res/fonts/Montserrat-BoldItalic.ttf");
	this->text_hp.setFont(this->font);
	this->text_hp.setFillColor(sf::Color(255,255,255));
	this->text_hp.setCharacterSize(12);
	this->text_mana.setFont(this->font);
	this->text_mana.setFillColor(sf::Color::White);
	this->text_mana.setCharacterSize(12);
	this->text_lvl.setFont(this->font);
	this->text_lvl.setFillColor(sf::Color::White);
	this->text_lvl.setCharacterSize(12);

	std::ostringstream oss;
	oss << this->player->getLvl();

	this->text_lvl.setString(oss.str());
	

}


Hud::~Hud()
{
}

sf::FloatRect Hud::invGetBounds()
{
	return inventory.getGlobalBounds();
}

void Hud::updateHp()
{
	double percerent = this->player->getCurrentHp() / ( this->player->getHp() / 100);
	double per_hp = 1.2 * percerent;
	this->hp.setTextureRect(sf::IntRect(0, 0, per_hp, 28));
	
	std::ostringstream oss;
	oss << this->player->getCurrentHp();
	oss << "/";
	oss << this->player->getHp();
	this->text_hp.setString(oss.str());
	this->text_hp.setPosition(this->hp.getPosition().x + 50,  this->hp.getPosition().y + 6);

}

void Hud::updatateMana()
{
	
}

void Hud::update(sf::Vector2f view_pos)
{
	this->bar.setPosition(view_pos.x - 640, view_pos.y - 360);
	//this->spell.setPosition(view_pos.x - 620, view_pos.y + 300);

	this->inventory.setPosition(view_pos.x + 595, view_pos.y + 300);
	//this->gift.setPosition(view_pos.x + 540, view_pos.y + 300);
	//this->door.setPosition(view_pos.x + 595, view_pos.y + 300);

	this->hp.setPosition(this->bar.getPosition().x + 74, this->bar.getPosition().y + 20);
	this->mana.setPosition(this->bar.getPosition().x + 73, this->bar.getPosition().y + 44);

	std::ostringstream oss;
	oss << this->player->getLvl();

	this->text_lvl.setString(oss.str());
	this->text_lvl.setPosition(this->bar.getPosition().x + 36, this->bar.getPosition().y + 68);
	updateHp();




}

void Hud::render(sf::RenderTarget * target)
{
	target->draw(this->hp);
	target->draw(this->mana);
	target->draw(this->bar);
	//target->draw(this->spell);
	target->draw(this->text_hp);
	target->draw(this->text_lvl);
	target->draw(this->inventory);
	//target->draw(this->gift);
	//target->draw(this->door);
}
