#include "../include/Game.hpp"

void Game::reset_bluebox(sf::Vector2f& t_blueboxpos, int& t_currentlevel, int& t_isdone, int& t_levelchange, int& t_currentlevellife, LevelData ld)
{
	t_blueboxpos.x = BLUEBOX_POS;
	t_blueboxpos.y = BLUEBOX_POS;

	if (t_currentlevel == 14) { 
		t_isdone = 1;
	}
	else {
		t_currentlevel += 1;
		t_levelchange = 1;
		t_currentlevellife = ld.lifecount(t_currentlevel);
	}
}

void Game::life_control(int& t_currentlevel, int& t_levelchange, sf::Vector2f& t_blueboxpos, int& t_currentlevellife, LevelData ld)
{
	t_currentlevellife -= 1;
	if (t_currentlevellife == 0 && !isredcolliding) {
		level_change(t_currentlevel, t_levelchange, t_blueboxpos, t_currentlevellife, ld);
	}
}

void Game::level_change(int& t_currentlevel, int& t_levelchange, sf::Vector2f& t_blueboxpos, int& t_currentlevellife, LevelData ld)
{
	t_currentlevel = 1;
	t_levelchange = 1;
	t_blueboxpos.x = BLUEBOX_POS;
	t_blueboxpos.y = BLUEBOX_POS;
	t_currentlevellife = ld.lifecount(t_currentlevel);
}

void Game::detect_collision(sf::Sprite box1, sf::Sprite box2, std::vector<sf::Sprite> bboxes, sf::RenderWindow& window, 
						   sf::Vector2f& t_blueboxpos, int& t_currentlevel, int& t_isdone, int& t_levelchange, int& t_currentlevellife, LevelData ld)
{
	sf::FloatRect boxone = box1.getGlobalBounds();

	sf::FloatRect boxtwo = box2.getGlobalBounds();

	if (boxone.intersects(boxtwo)) {
		isredcolliding = true;	
		window.clear();
		bboxes.clear();
		reset_bluebox(t_blueboxpos, t_currentlevel, t_isdone, t_levelchange, t_currentlevellife, ld);
	}
	else {
		isredcolliding = false;
	}
}