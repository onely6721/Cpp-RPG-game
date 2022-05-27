#include "Entity.h"



Entity::Entity()
{

}


Entity::~Entity()
{
}

void Entity::loadTexture(sf::Texture texture)
{
	this->texture = texture;
}

void Entity::loadSprite()
{
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 32));
}
