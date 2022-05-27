#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameObject
{
public:

	GameObject();
	GameObject(std::string path, float x, float y, float width, float height);
	~GameObject();

	void setX(int x) { m_x = x; };
	int getX() { return m_x; };

	void setY(int y) { m_y = y; };
	int getY() { return m_y; };

	void setWidth(int width) { m_width = width; };
	int getWidth() { return m_width; };

	void setHeight(int height) { m_height = height; };
	int getHeight() { return m_height; };

	sf::Sprite getSprite() { return m_sprite; };

protected:

	float m_x, m_y, m_width, m_height;
	std::string m_path;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

