#include <SFML/Main.hpp>
#include <SFML/System.hpp>

#include "../include/Screens.hpp"
#include "../include/LevelRenderer.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Single-Shot Maze",sf::Style::Fullscreen);
	window.setFramerateLimit(240);
	window.setKeyRepeatEnabled(false);

	Screens screen;
	LevelRenderer lr;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:

				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					lr.moveleft(window);
					break;

				case sf::Keyboard::Right:
					lr.moveright(window);
					break;
				case sf::Keyboard::Up:
					lr.moveup(window);
					break;
				case sf::Keyboard::Down:
					lr.movedown(window);
					break;
				case sf::Keyboard::BackSpace:
					lr.reset_puzzle();
					break;
				case sf::Keyboard::Escape: 
					screen.gotomenu(window);
					break;
				}
			}
		}
		screen.mainmenu(window);
		window.display();
	}
	return 0;
}