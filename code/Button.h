#pragma once
#include <SFML/Graphics.hpp> 
#include <string>
#include <iostream>

enum states {IDLE = 0, HOVER, ACTIVE};

class Button
{
public:
	Button(sf::Texture &texture, std::string text, float x_ind, float y_ind);
	
	virtual ~Button();

	bool onPressed();

	void setColor();
	void setPosition(int x, int y);

	void updateText();
	
	void update(sf::Vector2i &mousePos);
	void render(sf::RenderTarget *target);

private:
	
	states btn_state;
	float x_ind;
	float y_ind;

	sf::Text text;
	sf::Font font;

	sf::Texture texture;
	sf::Sprite sprite;

};

