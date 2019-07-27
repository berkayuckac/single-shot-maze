#ifndef  ONE_SHOT_MAZE_LEVEL_RENDERER_HPP
#define  ONE_SHOT_MAZE_LEVEL_RENDERER_HPP

#pragma once

#include <SFML/Graphics.hpp>

class LevelRenderer
{
public:
	LevelRenderer();
	int renderlevel(sf::RenderWindow& window);
	void moveleft(sf::RenderWindow& window);
	void moveright(sf::RenderWindow& window);
	void moveup(sf::RenderWindow& window);
	void movedown(sf::RenderWindow& window);
	void reset_puzzle();
private:
	sf::Texture t_blue, t_red, t_yellow, t_black;
	sf::Time elapsed;
	sf::Font font;
	sf::Clock clock;
	sf::Sprite boxcreator(int colorofbox, sf::Vector2f boxcoord);
	sf::Text timer();
	void renderui(sf::RenderWindow& window, sf::Font font, int lifecount);
	void createsprites();
};

#endif