#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h"

class MainMenuState :
	public State
{
public:
	MainMenuState(sf::RenderWindow *window, std::stack<State*> *states);
	virtual ~MainMenuState();

	void initButtons();
	void initVariables();
	void initTextures();
	void initSounds();
	void initCursor();

	void updateMouseInput(const float &dt);
	void updateInput(const float &dt);
	void updateButtons(const float &dt);
	void updateCursor();
	
	void renderCursor();

	void update(const float &dt);
	void render(sf::RenderTarget *target);



private:

	sf::Texture t_load_screen;
	sf::Sprite s_load_screen;

	sf::Sound mouse_click;
	sf::SoundBuffer buffer;
	sf::Music music;
	sf::Sprite cursor;

	std::map < std::string, Button* > buttons;
	std::map<std::string, sf::Texture> textures;


	sf::Sprite s_back;
};

