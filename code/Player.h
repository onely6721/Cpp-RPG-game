#pragma once
#include "Entity.h"
#include <iostream>
#include "Tile.h"
#include "Shell.h"

enum direction {up = 0,down = 1 , left = 2 , right = 3};

class Player :
	public Entity
{
public:
	Player(int lvl, float pos_x, float pos_y);
	virtual ~Player();

	void initSprite();
	void initVariables();
	void initHitbox();
	void initSound();
	
	void spawnArrow();

	void updateAttack(const float &dt);
	void updateShell(const float &dt);
	void updateAnimation(const float &dt);
	void updateHitbox();
	void updateMove(const float &dt);

	bool checkPathPassed(float player, float path, float dir);
	bool checkCollisonBody(sf::RectangleShape tile_rect);
	int getDir();
	int getLvl();
	void getDmg(double dmg);
	double getHp();
	double getCurrentHp();

	sf::RectangleShape *getRect();
	std::vector<Shell*> &getShell();

	void setHp(int hp);
	void setCurrentFrame(float current_frame);
	void setDir(direction dir);
	void setRun(bool running);
	void setAttack(bool attack);
	void setVelocity(sf::Vector2f velocity);
	void setPath(sf::Vector2f path);
	void setPathDir(sf::Vector2f path_dir);
	void setTarget(Entity *target);
	void setPosition(sf::Vector2f pos);

	void renderHitbox(sf::RenderTarget *target);
	void renderShell(sf::RenderTarget *target);

	void update(const float &dt);
	void render(sf::RenderTarget *target = nullptr);
	void move(const float dt, float dir_x, float dir_y);
	void moveToPoint();

private:

	Entity *target;
	Shell *arrow;
	Hitbox *hitbox;

	direction dir;

	sf::Vector2f velocity;
	sf::Vector2f path;
	sf::Vector2f path_dir;
	sf::Clock clock;
	sf::Sound arrow_sound;
	std::vector<Shell*> arrows;
	sf::SoundBuffer shootBuffer;

	double hp;
	double current_hp;
	double mana;
	double current_mana;
	double dmg;


	float current_frame;
	float attack_timer;
	
	int lvl;

	bool attack;
	bool attacking;
	bool running;

};

