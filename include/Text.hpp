#ifndef  ONE_SHOT_MAZE_TEXT_HPP
#define  ONE_SHOT_MAZE_TEXT_HPP

#pragma once

#include <SFML/Graphics/Text.hpp>

class Text
{
public:
	Text();
	sf::Text createtext(std::string string, sf::Color color, sf::Vector2f pos);
private:
	sf::Font font;
};

#endif 