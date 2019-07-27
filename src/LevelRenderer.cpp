#include <vector>

#include "../include/LevelRenderer.hpp"
#include "../include/Game.hpp"
#include "../include/LevelData.hpp"
#include "../include/Text.hpp"

using namespace std;

Game g;
LevelData ld;
Text txt;

sf::Sprite s_bluebox, s_redbox;
sf::Vector2f blueboxpos;

bool canmove = true;

int currentlevel{ 1 }; 
int currentlevellife{ 0 };
int isdone{ 0 };
int levelchange{ 0 };

const float SPACE_AMOUNT= 50.0f;
const float BLUEBOX_POS = 100.0f;

std::vector<sf::Sprite> blackboxes; 
std::vector<sf::Sprite> maze;

LevelRenderer::LevelRenderer()
{
	currentlevellife = ld.lifecount(currentlevel);
	t_blue.loadFromFile("lib/textures/lightblue.png");
	t_yellow.loadFromFile("lib/textures/white.png");
	t_red.loadFromFile("lib/textures/pink.png");
	t_black.loadFromFile("lib/textures/black.png");
	font.loadFromFile("lib/font/IndieFlower.ttf");
	blueboxpos.x = BLUEBOX_POS;
	blueboxpos.y = BLUEBOX_POS;
}

int LevelRenderer::renderlevel(sf::RenderWindow& window) 
{
	window.clear();
	
	//First level check
	if (currentlevel == 1) {
		createsprites();
	}
	//Levelchange check
	if (levelchange == 1) {
		createsprites();
		clock.restart();
		levelchange = 0;
	}

	//Draw maze
	for (int i = 0; i < maze.size(); i++) { 
		window.draw(maze[i]);
	}
	
	//Draw in-game UI
	renderui(window, font, currentlevellife);

	//Blue box 
	s_bluebox = boxcreator(0, sf::Vector2f(blueboxpos.x, blueboxpos.y)); 
	s_bluebox.setScale(0.75f, 0.75f);
	window.draw(s_bluebox);
	g.detect_collision(s_bluebox, s_redbox, blackboxes, window, blueboxpos, currentlevel, isdone, levelchange, currentlevellife, ld);
	
	//Time check
	string currenttime = timer().getString();
	if (!(stoi(currenttime) == 0)) {
		window.draw(timer());
	}
	else {
		g.level_change(currentlevel, levelchange, blueboxpos, currentlevellife, ld);
	}
	
	//Last level check
	if (isdone == 1) {
		isdone = 0;
		reset_puzzle();
		window.clear();
		return 1;
	}
	else {
		return 0;
	}
}

//Sprite-Box creation
void LevelRenderer::createsprites()
{
	blackboxes.clear();
	maze.clear();
	for (int i = 0; i < ld.maze_tiles(currentlevel).size(); i++) {
		for (int j = 0; j < ld.maze_tiles(currentlevel)[0].size(); j++) {
			if (ld.maze_tiles(currentlevel)[i][j] == 1) {
				sf::Sprite s_yellow = boxcreator(1, sf::Vector2f(((j + 1) * SPACE_AMOUNT), ((i + 1) * SPACE_AMOUNT)));
				s_yellow.setScale(0.75f, 0.75f);
				maze.push_back(s_yellow);
			}
			else if (ld.maze_tiles(currentlevel)[i][j] == 2) {
				sf::Sprite s_red = boxcreator(2, sf::Vector2f(((j + 1) * SPACE_AMOUNT), ((i + 1) * SPACE_AMOUNT)));
				s_red.setScale(0.75f, 0.75f);
				s_redbox = s_red;
				maze.push_back(s_red);
			}
			else if (ld.maze_tiles(currentlevel)[i][j] == 3) {
				sf::Sprite s_black = boxcreator(3, sf::Vector2f(((j + 1) * SPACE_AMOUNT), ((i + 1) * SPACE_AMOUNT)));
				s_black.setScale(0.75f, 0.75f);
				maze.push_back(s_black);
				blackboxes.push_back(s_black);
			}
		}
	}
}

sf::Sprite LevelRenderer::boxcreator(int colorofbox, sf::Vector2f boxcoord)
{
	sf::Sprite sprite;

	if (colorofbox == 0) {
		sprite.setTexture(t_blue);
	}
	else if (colorofbox == 1) {
		sprite.setTexture(t_yellow);
	}
	else if (colorofbox == 2) {
		sprite.setTexture(t_red);
	}
	else if (colorofbox == 3) {
		sprite.setTexture(t_black);
	}

	sprite.setPosition(sf::Vector2f(boxcoord));
	return sprite;
}

//Time UI
sf::Text LevelRenderer::timer()
{
	static sf::Text t_time;
	elapsed = clock.getElapsedTime();
	t_time.setFont(font);
	int time = (ld.timelimit(currentlevel) - elapsed.asSeconds());
	t_time.setString(to_string(time)); 
	t_time.setFillColor(sf::Color(214, 238, 255, 255));
	t_time.setPosition(sf::Vector2f(1800, 100.0f));
	return t_time;
}

//Game UI
void LevelRenderer::renderui(sf::RenderWindow& window, sf::Font font, int lifecount)
{
	window.draw(txt.createtext("Life Remaining :", sf::Color(138, 186, 243, 255), sf::Vector2f(1550.0f, 60.0f)));
	window.draw(txt.createtext(std::to_string(lifecount), sf::Color(214, 238, 255, 255), sf::Vector2f(1800.0f, 60.0f)));
	window.draw(txt.createtext(std::to_string(currentlevel), sf::Color(214, 238, 255, 255), sf::Vector2f(1800.0f, 25.0f)));
	window.draw(txt.createtext("Level No :", sf::Color(138, 186, 243, 255), sf::Vector2f(1550.0f, 25.0f)));
	window.draw(txt.createtext("Time Remaining :", sf::Color(138, 186, 243, 255), sf::Vector2f(1550.0f, 100.0f)));
}

//Movement
void LevelRenderer::moveleft(sf::RenderWindow& window)
{
	sf::Vector2f tempbluepos = blueboxpos;//create a temporary position
	tempbluepos.x > 0 ? tempbluepos.x = tempbluepos.x - SPACE_AMOUNT : tempbluepos.x;//check if its within the limits
	sf::Sprite tempblue = s_bluebox; //create a copy of bluebox sprite
	tempblue.setPosition(tempbluepos); //set temporary position to the temporary sprite
	sf::FloatRect blboxpos = tempblue.getGlobalBounds();

	//Check the temporary position with blackboxes for collision detection
	for (int i{ 0 }; i < blackboxes.size(); i++) {
		if (blboxpos.intersects(blackboxes[i].getGlobalBounds())) {
			canmove = false;
		}
	}

	if (canmove == true) {
		blueboxpos.x > 0 ? blueboxpos.x = blueboxpos.x - SPACE_AMOUNT : blueboxpos.x;
		g.life_control(currentlevel, levelchange, blueboxpos, currentlevellife, ld);
		renderui(window, font, currentlevellife);
	}

	canmove = true;
}

void LevelRenderer::moveright(sf::RenderWindow& window)
{ 
	sf::Vector2f tempbluepos = blueboxpos;
	tempbluepos.x < 1920 ? tempbluepos.x = tempbluepos.x + SPACE_AMOUNT : tempbluepos.x;
	sf::Sprite tempblue = s_bluebox; 
	tempblue.setPosition(tempbluepos); 
	sf::FloatRect blboxpos = tempblue.getGlobalBounds();

	for (int i{ 0 }; i < blackboxes.size(); i++) {
		if (blboxpos.intersects(blackboxes[i].getGlobalBounds())) {
			canmove = false;
		}
	}

	if (canmove == true) {
		blueboxpos.x < 1920 ? blueboxpos.x = blueboxpos.x + SPACE_AMOUNT : blueboxpos.x;
		g.life_control(currentlevel, levelchange, blueboxpos, currentlevellife, ld);
		renderui(window, font, currentlevellife);
	}

	canmove = true;
}

void LevelRenderer::moveup(sf::RenderWindow& window)
{
	sf::Vector2f tempbluepos = blueboxpos;
	tempbluepos.y > 0 ? tempbluepos.y = tempbluepos.y - SPACE_AMOUNT : tempbluepos.y;
	sf::Sprite tempblue = s_bluebox; 
	tempblue.setPosition(tempbluepos); 
	sf::FloatRect blboxpos = tempblue.getGlobalBounds();

	for (int i{ 0 }; i < blackboxes.size(); i++) {
		if (blboxpos.intersects(blackboxes[i].getGlobalBounds())) {
			canmove = false;
		}
	}

	if (canmove == true) {
		blueboxpos.y > 0 ? blueboxpos.y = blueboxpos.y - SPACE_AMOUNT : blueboxpos.y;
		g.life_control(currentlevel, levelchange, blueboxpos, currentlevellife, ld);
		renderui(window, font, currentlevellife);
	}

	canmove = true;
}

void LevelRenderer::movedown(sf::RenderWindow& window)
{
	sf::Vector2f tempbluepos = blueboxpos;
	tempbluepos.y < 1080 ? tempbluepos.y = tempbluepos.y + SPACE_AMOUNT : tempbluepos.y;
	sf::Sprite tempblue = s_bluebox; 
	tempblue.setPosition(tempbluepos); 
	sf::FloatRect blboxpos = tempblue.getGlobalBounds();

	for (int i{ 0 }; i < blackboxes.size(); i++) {
		if (blboxpos.intersects(blackboxes[i].getGlobalBounds())) {
			canmove = false;
		}
	}

	if (canmove == true) {
		blueboxpos.y < 1080 ? blueboxpos.y = blueboxpos.y + SPACE_AMOUNT : blueboxpos.y;
		g.life_control(currentlevel, levelchange, blueboxpos, currentlevellife, ld);
		renderui(window, font, currentlevellife);
	}

	canmove = true;
}

void LevelRenderer::reset_puzzle()
{
	currentlevel = 1;  
	isdone = 0;
	blueboxpos.x = BLUEBOX_POS;
	blueboxpos.y = BLUEBOX_POS;
	currentlevellife = ld.lifecount(currentlevel);
	g.level_change(currentlevel, levelchange, blueboxpos, currentlevellife, ld);
}