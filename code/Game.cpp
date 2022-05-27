#include "Game.h"



Game::Game()
{

	initWindow();
	initState();

	
}


Game::~Game()
{

}

void Game::initState()
{
	this->states.push(new MainMenuState(this->window,&this->states));

}

void Game::updateDt()
{
	this->dt = this->clock.getElapsedTime().asSeconds();
	clock.restart();
}
void Game::updateEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
		{
			window->close();
		}
	}

}

void Game::update()
{

	updateEvents();
	if (!states.empty())
	{
		states.top()->update(this->dt);
	}
}

void Game::render()
{
	this->window->clear();

	if (!states.empty())
	{
		states.top()->render(this->window);
	}
	
	this->window->display();

}



void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();

		
	}
}


void Game::initWindow()
{
	std::ifstream conf("Config/window.ini");

	std::string title = "Dungeon Hunter";
	sf::VideoMode window_size(1280, 720);
	unsigned framerate_limit = 120;
	bool vertycal_sync_enabled = 0;

	if (conf.is_open())
	{
		std::getline(conf, title);
		conf >> window_size.width >> window_size.height;
		conf >> framerate_limit;
		conf >> vertycal_sync_enabled;
	}

	this->window = new sf::RenderWindow(window_size,title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertycal_sync_enabled);

}
