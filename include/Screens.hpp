#ifndef  ONE_SHOT_MAZE_SCREENS_HPP
#define  ONE_SHOT_MAZE_SCREENS_HPP

#pragma once

#include <SFML/Graphics.hpp>

class Screens
{
public:
	Screens();
	void mainmenu(sf::RenderWindow &window);
	void puzzle(sf::RenderWindow& w);
	void about(sf::RenderWindow& window);
	void credits(sf::RenderWindow& w);
	void gotomenu(sf::RenderWindow& window);
	int screenid = 0;
private:
	sf::Texture t_lightblue,t_white,t_pink;
	sf::Font font;
	void checkmouseover(sf::Text t1,sf::Vector2f translatedpos, sf::RenderWindow& wind);
};

#endif