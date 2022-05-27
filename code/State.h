#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <stack>
#include <map>
#include <string>

class State
{
public:
	State(sf::RenderWindow *window, std::stack<State*> *states);
	virtual ~State();



	
	virtual void updateInput(const float &dt) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;
	
protected:
	
	
	sf::RenderWindow *window;
	std::map<std::string, sf::Texture> textures;
	
	std::stack <State*> *states;
	
};

