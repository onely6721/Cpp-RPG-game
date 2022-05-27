#include "blacout.h"



Blackout::Blackout()
{
	sf::Vector2f size(1280, 720);
	shape.setSize(size);
	shape.setFillColor(sf::Color(0, 0, 0, 127));
	
	this->opacity = 0;

	font.loadFromFile("res/fonts/Montserrat-BoldItalic.ttf");
	text.setFont(font);
	text.setString("12:31");
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(24);
}


Blackout::~Blackout()
{
}

void Blackout::updateTimer(sf::Vector2f pos)
{
	text.setPosition(pos.x + 500, pos.y - 340);
	std::string str;

	time = clock.getElapsedTime();

	std::ostringstream os;
	os << time.asSeconds();

	str = os.str();

	text.setString(str);


}

void Blackout::update(sf::Vector2f pos)
{
	updateTimer(pos);
	if (this->opacity > 150) opacity = 0;
		opacity++;
	shape.setFillColor(sf::Color(0, 0, 0, opacity));
	shape.setPosition(pos.x - 640, pos.y - 360);
}

void Blackout::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
