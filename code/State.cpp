#include "State.h"



State::State(sf::RenderWindow *window, std::stack<State*> *states)
{
	this->window = window;
	this->states = states;
}


State::~State()
{
}

