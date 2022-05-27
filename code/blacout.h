#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

class Blackout
{
public:
	Blackout();
	virtual ~Blackout();

	void updateTimer(sf::Vector2f pos);

	void update(sf::Vector2f pos);
	void render(sf::RenderTarget *target);



private:
	 float f_time;

	sf::Font font;
	sf::Text text;
	sf::RectangleShape shape;
	sf::Color color;
	sf::Clock clock;
	sf::Time time;
	int opacity;
};

