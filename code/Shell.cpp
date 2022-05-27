#include "Shell.h"



Shell::Shell(std::string path, float max_range, sf::Vector2f pos, sf::Vector2f dir_arrow, int dir_player, float speed)
{
	this->texture.loadFromFile(path);
	this->sprite.setTexture(this->texture);
	this->max_range = max_range;
	this->dir = dir_arrow;
	this->sprite.setTextureRect(sf::IntRect(0, 0, 5, 30));
	this->speed = speed;
	this->traveled_range = 0;
	this->dir_player = dir_player;
	sf::Vector2f size_hitbox;
	
	size_hitbox.x = 5;
	size_hitbox.y = 30;
	initHitbox(size_hitbox, this->sprite.getPosition());
	double angle = acos(dir.x * dir.y) * 57.2957795;
	this->sprite.rotate(90.f);

	switch (dir_player)
	{
	case 0:
		this->sprite.setPosition(pos.x + 30, pos.y + 60);
		this->sprite.rotate(angle);
		this->hitbox->rotate(180.f);
		break;
	case 1:
		this->sprite.setPosition(pos.x + 28, pos.y + 3);
		this->sprite.rotate(angle +180.f);
		break;
	case 2:
		this->sprite.setPosition(pos.x + 31, pos.y + 36);
		this->sprite.rotate(-270.f - angle);
		this->hitbox->rotate(-90.f + angle);
		break;
	case 3:
		this->sprite.setPosition(pos.x + 13, pos.y + 38);
		this->sprite.rotate(-90.f - angle);
		this->hitbox->rotate(180.f);
		break;
	}



}


Shell::~Shell()
{
	delete this->hitbox;
}

void Shell::initHitbox(sf::Vector2f size, sf::Vector2f pos)
{
	hitbox = new Hitbox(size, pos);
}

sf::RectangleShape * Shell::getRect()
{
	return this->hitbox->getRect();
}



bool Shell::checkCollision(sf::RectangleShape &shape)
{
	return hitbox->checkCollision(shape);
}

bool Shell::checkEndPoint()
{
	if (traveled_range > max_range)
		return true;
	else
		return false;

}

void Shell::updateHitbox()
{
	hitbox->update(this->sprite.getPosition());
}

void Shell::update(const float & dt)
{
	
	this->sprite.move(dir.x * dt * speed, dir.y * dt * speed);
	this->traveled_range += (abs(dir.x) + abs(dir.y)) * dt * speed;
	updateHitbox();


}

void Shell::render(sf::RenderTarget * target)
{
	target->draw(this->sprite);

}

void Shell::move(const float dt, float dir_x, float dir_y)
{
}

void Shell::setPosition(sf::Vector2f pos)
{
}
