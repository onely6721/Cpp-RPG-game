#include "GameObject.h"



GameObject::GameObject(std::string path, float x, float y, float width, float height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_path = path;

	m_texture.loadFromFile(m_path);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(m_x, m_y, m_width, m_height));


}
GameObject::GameObject()
{

}



GameObject::~GameObject()
{

}
