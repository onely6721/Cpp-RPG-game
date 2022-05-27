#include "Button.h"





Button::Button(sf::Texture &texture, std::string text, float x_ind, float y_ind)
{
	this->texture = texture;
	sprite.setTexture(this->texture);

	
	this->font.loadFromFile("res/fonts/11872.otf");
	
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::Black);
	this->text.setString(text);
	this->text.setCharacterSize(24);

	this->x_ind = x_ind;
	this->y_ind = y_ind;
}

Button::~Button()
{
}

bool Button::onPressed()
{
	if (btn_state == ACTIVE)
		return true;
	else
		return false;
}



void Button::setColor()
{
	sprite.setColor(sf::Color(103,243,249));
}

void Button::setPosition(int x, int y)
{
	sprite.setPosition(x, y);
}

void Button::updateText()
{
	sf::Vector2f temp_pos = this->sprite.getPosition();
	temp_pos.x += x_ind;
	temp_pos.y += y_ind;

	this->text.setPosition(temp_pos);

}

void Button::update(sf::Vector2i &mousePos)
{
	updateText();

	this->btn_state = IDLE;
	 
	if (this->sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		this->btn_state = HOVER;
		 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->btn_state = ACTIVE;
		}
	}

	switch (btn_state) 
	{
		case IDLE:
			this->sprite.setColor(sf::Color(0, 150, 255));
			this->text.setFillColor(sf::Color(192,192,192));
			break;
		case HOVER:
			this->sprite.setColor(sf::Color(255,127,127));
			this->text.setFillColor(sf::Color::White);
			break;
		case ACTIVE:
			break;
	}

}

void Button::render(sf::RenderTarget * target)
{
	target->draw(this->sprite);
	target->draw(this->text);
	
}
