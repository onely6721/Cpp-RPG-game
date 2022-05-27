#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Hitbox.h"
#include <string>
#include <queue>
#include <random>


class Entity
{
public:
	Entity();
	virtual ~Entity();

	void loadTexture(sf::Texture texture);
	void loadSprite();
	virtual sf::RectangleShape *getRect() = 0;
	sf::Vector2f getPos() { return this->sprite.getPosition(); }

	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;
	virtual void move(const float dt,float dir_x, float dir_y) = 0;
	virtual void setPosition(sf::Vector2f pos) = 0;



protected:

	sf::Sprite sprite;
	sf::Texture texture;
	float speed;

};

