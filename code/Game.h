#pragma once
#include <sstream>
#include <string>
#include <fstream>
#include "Player.h"
#include "map.h"
#include <SFML/Graphics.hpp>
#include <stack>
#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"

class Game
{
public:

	Game();
	virtual ~Game();


	void initState();
	void initWindow();


	void updateDt();
	void updateEvents();
	void update();
	void render();
	void run();

private:



	sf::RenderWindow *window;
	sf::Event event;
	sf::Clock clock;
	float dt;

	std::stack<State*> states;

};

