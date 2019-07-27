#ifndef  ONE_SHOT_MAZE_GAME_HPP
#define  ONE_SHOT_MAZE_GAME_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp> 

#include "LevelData.hpp"

class Game 
{
public:
	void life_control(int& t_currentlevel, int& t_levelchange, sf::Vector2f& t_blueboxpos, int& t_currentlevellife, LevelData ld);
	void level_change(int &t_currentlevel, int &t_levelchange, sf::Vector2f &t_blueboxpos, int &t_currentlevellife, LevelData ld);
	void detect_collision(sf::Sprite box1, sf::Sprite box2, std::vector<sf::Sprite> bboxes, sf::RenderWindow& window,
						 sf::Vector2f& t_blueboxpos, int& t_currentlevel, int& t_isdone, int& t_levelchange, int& t_currentlevellife, LevelData ld);
	bool canmove = true;
	bool isredcolliding = false;
private:
	void reset_bluebox(sf::Vector2f& t_blueboxpos, int& t_currentlevel, int& t_isdone, int& t_levelchange, int& t_currentlevellife, LevelData ld);
	const float BLUEBOX_POS = 100.0f;
};

#endif