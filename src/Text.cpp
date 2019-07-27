#include "../include/Text.hpp"

Text::Text()
{
	font.loadFromFile("lib/font/IndieFlower.ttf");
}

sf::Text Text::createtext(std::string string, sf::Color color, sf::Vector2f pos)
{
	sf::Text txt;
	//set font 
	txt.setFont(font);
	//set string
	txt.setString(string);
	//set color
	txt.setFillColor(color);
	//set position 
	txt.setPosition(pos);
	return txt;
}
