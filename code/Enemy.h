#pragma once
#include "Entity.h"
#include "Player.h"

enum state_enemy { STAY = 0, RUNNING = 1, ATTACK = 2 };

class Enemy :
	public Entity
{
public:
	Enemy(sf::Vector2f pos, sf::Texture &texture);
	virtual ~Enemy();
	void initHibox();
	void initAttackRadius();
	

	sf::RectangleShape *getRect();

	sf::FloatRect getGlobalBounds();
	double getHp();

	void setDir(int dir);
	

	void getDmg(float dmg);

	bool checkPathPassed(float player, float path, float dir);
	void setTarget(Player *target);
	void updateHp();
	void updateStates(const float &dt);
	void updateRunning(const float &dt);
	void updateStay(const float &dt);
	void updateAttack(const float &dt);
	void updateAnimation(const float &dt);
	void updateHpBar();
	
	void renderHpBar(sf::RenderTarget *target);

	void update(const float &dt);

	void render(sf::RenderTarget *target);

	void moveToPoint();
	void move(const float dt, float dir_x, float dir_y);
	void setPosition(sf::Vector2f pos);

private:
	
	Hitbox *hitbox;
	Hitbox *attack_radius;
	

	Player *target;
	
	sf::Sprite hp_bar;
	sf::Clock clock;

	sf::Vector2f path;
	sf::Vector2f path_dir;
	sf::Vector2f velocity;

	state_enemy current_state;
	float current_frame;
	float attack_timer;
	
	int dir;
	double hp, dmg;
	double current_hp;
};

