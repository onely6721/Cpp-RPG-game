#include "Enemy.h"



Enemy::Enemy(sf::Vector2f pos, sf::Texture &texture)
{
	this->texture.loadFromFile("res/img/orce.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 704, 64, 64));
	this->sprite.setPosition(pos);

	this->current_frame = 0;
	this->velocity.x = 0;
	this->velocity.y = 0;
	current_state = STAY;
	this->speed = 50;
	this->hp = 2000;
	this->dmg = 20;
	this->attack_timer = 0;
	this->clock.restart();
	this->current_hp = this->hp;
	this->hp_bar.setTexture(texture);

	initHibox();
	initAttackRadius();
}


Enemy::~Enemy()
{
	delete hitbox;
	delete attack_radius;
}

void Enemy::initHibox()
{
	sf::Vector2f temp_size(32, 48);
	hitbox = new Hitbox(temp_size, this->sprite.getPosition(), 16,16);
}

void Enemy::initAttackRadius()
{
	sf::Vector2f temp_size(500, 500);
	attack_radius = new Hitbox(temp_size,this->sprite.getPosition(),-218,-218);
}




sf::RectangleShape * Enemy::getRect()
{
	return this->hitbox->getRect();
}

sf::FloatRect Enemy::getGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

double Enemy::getHp()
{
	return current_hp;
}

void Enemy::updateAnimation(const float &dt)
{
	float temp_speed = 10;
	if (this->current_state == RUNNING)
	{
		if (this->current_frame > 9) { this->current_frame = 0; }

		if (dir == 0)
		{
			this->sprite.setTextureRect(sf::IntRect(int(this->current_frame) * 64, 512, 64, 64));
			this->current_frame += dt * temp_speed;
		}
		if (dir == 1)
		{
			this->sprite.setTextureRect(sf::IntRect(int(this->current_frame) * 64, 640, 64, 64));
			this->current_frame += dt * temp_speed;
		}
		if (dir == 2)
		{
			this->sprite.setTextureRect(sf::IntRect(int(this->current_frame) * 64, 576, 64, 64));
			this->current_frame += dt * temp_speed;
		}
		if (dir == 3)
		{
			this->sprite.setTextureRect(sf::IntRect(int(this->current_frame) * 64, 704, 64, 64));
			this->current_frame += dt * temp_speed;
		}
	}

	if (this->current_state == ATTACK)
	{
		if (this->current_frame > 8) { this->current_frame = 0; }

		if (dir == 0)
		{
			this->sprite.setTextureRect(sf::IntRect(int(this->current_frame) * 64, 256, 64, 64));
			this->current_frame += dt * temp_speed;
		}
		if (dir == 1)
		{
			this->sprite.setTextureRect(sf::IntRect(int(this->current_frame) * 64, 384, 64, 64));
			this->current_frame += dt * temp_speed;
		}
		if (dir == 2)
		{
			this->sprite.setTextureRect(sf::IntRect(int(this->current_frame) * 64, 320, 64, 64));
			this->current_frame += dt * temp_speed;
		}
		if (dir == 3)
		{
			this->sprite.setTextureRect(sf::IntRect(int(this->current_frame) * 64, 448, 64, 64));
			this->current_frame += dt * temp_speed;
		}
	}
}

void Enemy::updateHpBar()
{
	double percent =  this->current_hp / (this->hp / 100);
	double per_hp = 0.3 * percent;

	this->hp_bar.setTextureRect(sf::IntRect(0, 0, per_hp, 4));
	this->hp_bar.setPosition(this->sprite.getPosition().x + 16, this->sprite.getPosition().y + 13);
}

void Enemy::renderHpBar(sf::RenderTarget *target)
{
	target->draw(this->hp_bar);
}

void Enemy::setDir(int dir)
{
	this->dir = dir;

}

void Enemy::getDmg(float dmg)
{
	this->current_hp -= dmg;
	
}

bool Enemy::checkPathPassed(float player, float path, float dir)
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

void Enemy::setTarget(Player *target)
{

	this->target = target;
}

void Enemy::updateHp()
{
	
}

void Enemy::updateStates(const float & dt)
{
	if (this->current_state == STAY)
		updateStay(dt);
	if (this->current_state == RUNNING)
		updateRunning(dt);
	if (this->current_state == ATTACK)
		updateAttack(dt);
}

void Enemy::updateRunning(const float &dt)
{

	if (this->target != nullptr)
	{
		this->path.x = this->target->getPos().x;
		this->path.y = this->target->getPos().y;
		if (this->sprite.getPosition().x <= this->target->getPos().x)
		{
			path_dir.x = 1;
		}
		else
		{
			path_dir.x = -1;
		}
		if (this->sprite.getPosition().y <= this->target->getPos().y)
		{
			path_dir.y = 1;
		}
		else
		{
			path_dir.y = -1;
		}


		if ((!checkPathPassed(this->sprite.getPosition().y - 50, path.y, path_dir.y)
			or !checkPathPassed(this->sprite.getPosition().y + 50, path.y, path_dir.y))
			&& (!checkPathPassed(this->sprite.getPosition().x - 50, path.x, path_dir.x)
			or !checkPathPassed(this->sprite.getPosition().x + 50, path.x, path_dir.x)))
		{
			this->current_state = ATTACK;
			this->current_frame = 0;
		}
		else
		{
			moveToPoint();
		}
	}
	else
	{

		if (this->dir == 0)
		{
			if (this->sprite.getPosition().y < this->path.y)
			{
				this->current_state = STAY;
				this->velocity.x = 0;
				this->velocity.y = 0;
			}

		}

		if (this->dir == 1)
		{
			if (this->sprite.getPosition().y > this->path.x)
			{
				this->current_state = STAY;
				this->velocity.x = 0;
				this->velocity.y = 0;
			}
		}

		if (this->dir == 2)
		{
			if (this->sprite.getPosition().x < this->path.x)
			{
				this->current_state = STAY;
				this->velocity.x = 0;
				this->velocity.y = 0;
			}
		}

		if (this->dir == 3)
		{
			if (this->sprite.getPosition().x > this->path.x)
			{
				this->current_state = STAY;
				this->velocity.x = 0;
				this->velocity.y = 0;
			}
		}
	}

	this->sprite.move(velocity *dt * this->speed);
}

void Enemy::updateStay(const float &dt)
{
	this->dir = rand() % 2 + 2;

	/*if (this->dir == 0)
	{
		path.x = this->sprite.getPosition().x;
		path.y = this->sprite.getPosition().y - 50;
		velocity.x = 0;
		velocity.y = -1;
		current_state = RUNNING;

	}

	if (this->dir == 1)
	{
		path.x = this->sprite.getPosition().x;
		path.y = this->sprite.getPosition().y + 50;
		velocity.x = 0;
		velocity.y = 1;
		current_state = RUNNING;
	}*/

	if (this->dir == 2)
	{
		path.x = this->sprite.getPosition().x - 50;
		path.y = this->sprite.getPosition().y;
		velocity.x = -1;
		velocity.y = 0;
		current_state = RUNNING;
	}

	else 
	{
		path.x = this->sprite.getPosition().x + 50;
		path.y = this->sprite.getPosition().y;
		velocity.x = 1;
		velocity.y = 0;
		current_state = RUNNING;
	}

	
}


void Enemy::updateAttack(const float &dt)
{
	this->path.x = this->target->getPos().x;
	this->path.y = this->target->getPos().y;
	if (this->sprite.getPosition().x <= this->target->getPos().x)
	{
		path_dir.x = 1;
	}
	else
	{
		path_dir.x = -1;
	}
	if (this->sprite.getPosition().y <= this->target->getPos().y)
	{
		path_dir.y = 1;
	}
	else
	{
		path_dir.y = -1;
	}

	if ((!checkPathPassed(this->sprite.getPosition().y - 50, path.y, path_dir.y)
		or !checkPathPassed(this->sprite.getPosition().y + 50, path.y, path_dir.y))
		&& (!checkPathPassed(this->sprite.getPosition().x - 50, path.x, path_dir.x)
		or !checkPathPassed(this->sprite.getPosition().x + 50, path.x, path_dir.x)))
	{
		if (attack_timer < 1)
		{
			this->attack_timer = this->clock.getElapsedTime().asSeconds();

		}
		else
		{
			this->clock.restart();
			this->target->getDmg(this->dmg);
			this->attack_timer = 0;
		}
		
	} 
	else
	{
		this->current_state = RUNNING;
	}

}

void Enemy::update(const float & dt)
{
	this->hitbox->update(this->sprite.getPosition());
	this->attack_radius->update(this->sprite.getPosition());
	updateStates(dt);
	updateAnimation(dt);
	updateHpBar();


}

void Enemy::render(sf::RenderTarget * target)
{
	target->draw(this->sprite);
	renderHpBar(target);

}

void Enemy::moveToPoint()
{
	if ((!checkPathPassed(this->sprite.getPosition().y - 30, path.y, path_dir.y)
		or !checkPathPassed(this->sprite.getPosition().y + 30, path.y, path_dir.y))
		&& (!checkPathPassed(this->sprite.getPosition().x - 30, path.x, path_dir.x)
		or !checkPathPassed(this->sprite.getPosition().x + 30, path.x, path_dir.x)))
	{
		this->current_state = ATTACK;
	}
	else
	{
		this->current_state = RUNNING;
	}

	if (this->current_state == RUNNING)
	{
		int i;
		float range_x;
		float range_y;

		range_x = abs(this->sprite.getPosition().x - path.x);
		range_y = abs(this->sprite.getPosition().y - path.y);

		if (checkPathPassed(this->sprite.getPosition().x+10, path.x, path_dir.x))
		{
			i = 1;
		}
		else if (checkPathPassed(this->sprite.getPosition().y, path.y, path_dir.y))
		{
			i = 2;
		}
		else
		{
			this->current_state = ATTACK;
			i = 0;
		}

		if (i == 1)
		{

			this->velocity.x = path_dir.x;
			this->velocity.y = 0;
			if (path_dir.x == 1)
				this->dir = 3;
			else
				this->dir = 2;
		}

		if (i == 2)
		{
			this->velocity.x = 0;
			this->velocity.y = path_dir.y;
			if (path_dir.y == 1)
				this->dir = 1;
			else
				this->dir = 0;
		}

	}



}

void Enemy::move(const float dt, float dir_x, float dir_y)
{
}

void Enemy::setPosition(sf::Vector2f pos)
{
	
}

