#include "MainMenuState.h"



MainMenuState::MainMenuState(sf::RenderWindow *window, std::stack<State*> *states)
	:State(window,states)
{
	this->t_load_screen.loadFromFile("res/img/background/load_screen.png");
	this->s_load_screen.setTexture(this->t_load_screen);
	this->s_load_screen.setPosition(0, 0);
	this->window->draw(s_load_screen);

	initTextures();
	initVariables();
	initButtons();
	initSounds();
	initCursor();
}


MainMenuState::~MainMenuState()
{
}

void MainMenuState::initButtons()
{
	buttons["start"] = new Button(textures["button"],"Start", 70, 14);
	buttons["start"]->setPosition(540, 230);
	//buttons["settings"] = new Button(textures["button"], "Opth", 70, 14);
	//buttons["settings"]->setPosition(540, 300);
	buttons["exit"] = new Button(textures["button"], "Exit", 75,14);
	buttons["exit"]->setPosition(540, 300);
}

void MainMenuState::initVariables()
{
	s_back.setTexture(textures["background"]);
	this->window->setMouseCursorVisible(false);
	
}

void MainMenuState::initTextures()
{
	sf::Texture t_back;
	t_back.loadFromFile("res/img/background/back.png");
	textures.insert(std::pair<std::string, sf::Texture>("background", t_back) );

	sf::Texture t_button;
	t_button.loadFromFile("res/img/buttons/button1.png");

	textures.insert(std::pair<std::string, sf::Texture>("button", t_button));

	sf::Texture t_cursor;
	t_cursor.loadFromFile("res/img/cursor.png");
	textures.insert(std::pair<std::string, sf::Texture>("cursor", t_cursor));
	
}

void MainMenuState::initSounds()
{
	music.openFromFile("res/sound/sins.ogg");
	music.setVolume(5);


	buffer.loadFromFile("res/sound/mouse/click2.ogg");

	this->mouse_click.setBuffer(buffer);
}

void MainMenuState::initCursor()
{
	this->cursor.setTexture(textures["cursor"]);
	this->cursor.setColor(sf::Color(255, 255, 255));
}



void MainMenuState::updateMouseInput(const float & dt)
{

	sf::Vector2i position;
	position.x = 300;
	position.y = 300;
	
	
}

void MainMenuState::updateInput(const float & dt)
{

}

void MainMenuState::updateButtons(const float & dt)
{

	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);

	

	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->update(mousePos);

		if (it->first == "start")
			if (it->second->onPressed())
			{
				this->window->draw(s_load_screen);

				this->mouse_click.play();
				this->music.stop();
				this->states->push(new GameState(this->window, this->states));
			}
		
		//if (it->first == "settings")
		//	if (it->second->onPressed())
		//	{
		//		if(this->mouse_click.getStatus() != sf::Music::Playing)
		//			this->mouse_click.play();
		//	}

		if (it->first == "exit")
			if (it->second->onPressed())
			{
				this->mouse_click.play();
				this->window->close();
			}
	}



}

void MainMenuState::updateCursor()
{
	sf::Vector2i pos_mouse = sf::Mouse::getPosition(*this->window);
	this->cursor.setPosition(pos_mouse.x , pos_mouse.y);
}

void MainMenuState::renderCursor()
{
	this->window->draw(this->cursor);
}

void MainMenuState::update(const float & dt)
{
	//if (music.getStatus() != sf::Music::Playing)
	//{
	//	music.play();
	//	music.setLoop(true);
	//}

	updateInput(dt);
	updateMouseInput(dt);
	updateButtons(dt);
	updateCursor();
	
}

void MainMenuState::render(sf::RenderTarget * target)
{
	target->draw(s_back);

	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
			it->second->render(target);
	}

	renderCursor();
}
