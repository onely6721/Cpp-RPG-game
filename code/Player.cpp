#include "Player.h"



Player::Player(int lvl, float pos_x, float pos_y)
{

	initSprite();
	initVariables();
	initHitbox();
	initSound();

	this->lvl = lvl;
	this->sprite.setPosition(pos_x, pos_y);
}


Player::~Player()
{
}



void Player::initSprite()
{
	sf::Texture temp;
	temp.loadFromFile("res/img/player.png");

	loadTexture(temp);
	loadSprite();

	
	
}

void Player::initVariables()
{
	this->attack = false;
	this->running = false;
	this->speed = 100;
	this->dir = down;
	this->velocity.x = 0;
	this->velocity.y = 0;
	this->current_frame = 0;
	this->path.x = 0;
	this->path.y = 0;
	this->path_dir.x = 0;
	this->path_dir.y = 0;
	this->attack_timer = 0;
	this->hp = 100;
	this->dmg = 200;
	this->current_hp = 100;
	

}

void Player::initHitbox()
{
	sf::Vector2f pos = this->sprite.getPosition();
	sf::Vector2f size(24,22);

	
	this->hitbox = new Hitbox(size, pos,20,40);
	
}

void Player::initSound()
{
	
	shootBuffer.loadFromFile("res/sound/arrow.ogg");
	arrow_sound.setBuffer(shootBuffer);
	arrow_sound.setVolume(10);
}

void Player::spawnArrow()
{
	sf::Vector2f point;
	sf::Vector2f t_dir;

	if (this->target != nullptr)
	{
		point.x = this->target->getPos().x - this->sprite.getPosition().x;
		point.y = this->target->getPos().y - this->sprite.getPosition().y;
		float len = sqrt(point.x* point.x + point.y * point.y);
		point.x = point.x / len;
		point.y = point.y / len;
		bool added = false;

		for (int i = 0; i < arrows.size(); i++)
		{
			if (arrows[i] == nullptr)
			{
				this->arrows[i] = new Shell("res/img/arrow.png", 500,this->sprite.getPosition(), point,int(this->dir),500);
				added = true;
				break;
			}
		}
		if (!added)
			arrows.push_back(new Shell("res/img/arrow.png", 500,this->sprite.getPosition(), point,int(this->dir), 500));
	}
	
}

void Player::updateAttack(const float &dt)
{
	this->attacking = false;

	if (this->target != nullptr && this->attack)
	{
		float range_x, range_y;
		direction priority_dir;

		range_x =  abs(this->sprite.getPosition().x - this->target->getPos().x);
		range_y =  abs(this->sprite.getPosition().y  - this->target->getPos().y);


		if (this->target->getPos().x < this->sprite.getPosition().x)
		{
			this->path_dir.x = -1;
		}
		else
		{
			this->path_dir.x = 1;
		}
		if (this->target->getPos().y < this->sprite.getPosition().y)
		{
			this->path_dir.y = -1;
		}
		else
		{
			this->path_dir.y = 1;
		}

		if (range_x >= range_y)
		{
			if (path_dir.x == -1)
				priority_dir = left;
			else
				priority_dir = right;
		}
		else
		{
			if (path_dir.y == -1)
				priority_dir = up;
			else
				priority_dir = down;
		}

		if (range_x > range_y)
		{
			if (range_x < 300)
				this->attacking = true;
		}
		else
		{
			if (range_y < 300)
				this->attacking = true;
		}
		
		if (attacking)
		{
			this->running = false;
			this->dir = priority_dir;
			if (this->attack_timer < 1)
			{
				this->attack_timer = this->clock.getElapsedTime().asSeconds();
			
			}
			else
			{
				
				spawnArrow();
				this->arrow_sound.play();
				this->clock.restart();
				this->attack_timer = 0;
			}
		}
		else
		{
			running = true;
		}
	} 

}

void Player::updateShell(const float &dt)
{
	for (int i = 0; i < arrows.size(); i++)
	{
		if (arrows[i] != nullptr)
		{
			this->arrows[i]->update(dt);
			if (arrows[i]->checkEndPoint())
			{
				delete arrows[i];
				arrows[i] = nullptr;
			}
		}
	}

	if (arrow != nullptr)
	{
		this->arrow->update(dt);
		if (this->arrow->checkEndPoint())
		{
			delete this->arrow;
			this->arrow = nullptr;
		}
	}
}

void Player::updateAnimation(const float & dt)
{
	float temp_speed =  25;

	if (!attacking)
	{

		if (this->current_frame > 9) { current_frame = 0; }

		switch (dir)
		{
		case up:
			if (running)
				this->sprite.setTextureRect(sf::IntRect(int(current_frame) *64,64,64,64));
			else
				this->sprite.setTextureRect(sf::IntRect(0, 64, 64, 64));
			break;
		case down:
			if (running)
				this->sprite.setTextureRect(sf::IntRect(int(current_frame) * 64, 0, 64, 64));
			else
				this->sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
			break;
		case left:
			if (running)
				this->sprite.setTextureRect(sf::IntRect(int(current_frame) * 64, 192, 64, 64));
			else
				this->sprite.setTextureRect(sf::IntRect(0, 192, 64, 64));
			break;
		case right:
			if (running)
				this->sprite.setTextureRect(sf::IntRect(int(current_frame) * 64, 128, 64, 64));
			else
				this->sprite.setTextureRect(sf::IntRect(0, 128, 64, 64));
			break;
		}

		current_frame += dt * temp_speed;
	}
	
	 if (attacking)
	{
		if (this->current_frame > 13) { current_frame = 0; }
		switch (dir)
		{
		case up:
			this->sprite.setTextureRect(sf::IntRect(int(current_frame) * 64, 256, 64, 64));
			break;
		case down:
			this->sprite.setTextureRect(sf::IntRect(int(current_frame) * 64, 384, 64, 64));
			break;
		case left:
			this->sprite.setTextureRect(sf::IntRect(int(current_frame) * 64, 320, 64, 64));
			break;
		case right:
			this->sprite.setTextureRect(sf::IntRect(int(current_frame) * 64, 448, 64, 64));
			break;
		}
		current_frame += dt * temp_speed;
	}

}

void Player::updateHitbox()
{
	sf::Vector2f pos = this->sprite.getPosition();
	this->hitbox->update(pos);
}

void Player::updateMove(const float &dt)
{
	moveToPoint();
	this->sprite.move(velocity.x  * dt * speed,  velocity.y * dt * speed);
}

bool Player::checkPathPassed(float player, float path, float dir)
{
	if (dir == 1)
	{
		if (player <= path)
			return true;
		else
			return false;
	}

	if (dir == -1)
	{
		if (player >= path)
			return true;
		else
			return false;
	}
	return false;

}

bool Player::checkCollisonBody(sf::RectangleShape tile_rect)
{
	return this->hitbox->checkCollision(tile_rect);
}

int Player::getDir()
{
	return dir;
}

int Player::getLvl()
{
	return this->lvl;
}

void Player::getDmg(double dmg)
{
	this->current_hp -= dmg;
}

double Player::getHp()
{
	return  this->hp;
}

double Player::getCurrentHp()
{
	return this->current_hp;
}

sf::RectangleShape * Player::getRect()
{
	return hitbox->getRect();
}

std::vector<Shell*>  &Player::getShell()
{
	return  arrows;
}

void Player::setHp(int hp)
{
	this->current_hp = hp;
}

void Player::setCurrentFrame(float current_frame)
{
	this->current_frame = current_frame;
}

void Player::setDir(direction dir)
{
	this->dir = dir;
}

void Player::setRun(bool running)
{
	this->running = running;
}

void Player::setAttack(bool attack)
{
	this->attack = attack;
}

void Player::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Player::setPath(sf::Vector2f path)
{
	this->path = path;
}

void Player::setPathDir(sf::Vector2f path_dir)
{
	this->path_dir = path_dir;
}

void Player::setTarget(Entity *target)
{
	this->target = target;
}



void Player::renderHitbox(sf::RenderTarget * target)
{
	this->hitbox->render(target);
}

void Player::renderShell(sf::RenderTarget * target)
{
	for (int i = 0; i < arrows.size(); i++)
	{
		if (arrows[i] != nullptr)
		{
			arrows[i]->render(target);
		}

	}
}

void Player::update(const float & dt)
{
	updateMove(dt);
	updateAttack(dt);
	updateAnimation(dt);
	updateHitbox();
	updateShell(dt);

}

void Player::render(sf::RenderTarget * target)
{
	target->draw(this->sprite);
	renderShell(target);

}

void Player::move(const float dt, float dir_x, float dir_y)
{
	sprite.move(dir_x*dt*speed, dir_y*dt*speed);
}

void Player::moveToPoint()
{
	if (this->running == true)
	{
		int i;
		float range_x;
		float range_y;

		range_x = abs(this->sprite.getPosition().x - path.x);
		range_y = abs(this->sprite.getPosition().y - path.y);

		if (abs(range_x - range_y) > 1 && checkPathPassed(this->sprite.getPosition().x, path.x, path_dir.x))
		{
			i = 1;
		}
		else if (checkPathPassed(this->sprite.getPosition().y, path.y, path_dir.y))
		{
			i = 2;
		}
		else
		{
			running = false;
			i = 0;
		}

		if (i == 1)
		{

			this->velocity.x = path_dir.x;
			this->velocity.y = 0;
			if (path_dir.x == 1)
				this->dir = right;
			else
				this->dir = left;
		}

		if (i == 2)
		{
			this->velocity.y = path_dir.y;
			this->velocity.x = 0;
			if (path_dir.y == 1)
				this->dir = down;
			else
				this->dir = up;
		}

		if (!checkPathPassed(this->sprite.getPosition().y, path.y, path_dir.y) && !checkPathPassed(this->sprite.getPosition().x, path.x, path_dir.x))
		{
			this->running = false;
		}
	}
	else
	{
		velocity.x = 0;
		velocity.y = 0;
	}
}

void Player::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

