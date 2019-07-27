#include <memory>
#include <SFML/Window/Mouse.hpp>

#include "../include/Screens.hpp"
#include "../include/LevelRenderer.hpp"
#include "../include/Text.hpp"

Text t;
std::unique_ptr<LevelRenderer> lr(new LevelRenderer);

Screens::Screens()
{
	t_lightblue.loadFromFile("lib/textures/lightblue.png");
	t_white.loadFromFile("lib/textures/white.png");
	t_pink.loadFromFile("lib/textures/pink.png");
}

void Screens::mainmenu(sf::RenderWindow &window) 
{
	window.clear();
	if (screenid == 0) {
		//Icon boxes
		sf::Sprite lb, w, p;
		lb.setTexture(t_lightblue);
		lb.setPosition(410.0f, 350.0f);
		lb.setScale(2.0f, 2.0f);
		w.setTexture(t_white);
		w.setPosition(550.0f, 350.0f);
		w.setScale(2.0f, 2.0f);
		p.setTexture(t_pink);
		p.setPosition(550.0f, 490.0f);
		p.setScale(2.0f, 2.0f);
		window.draw(lb);
		window.draw(w);
		window.draw(p);

		//Icon texts
		window.draw(t.createtext("single-", sf::Color(138, 186, 243, 255), sf::Vector2f(720.0f, 440.0f)));
		window.draw(t.createtext("shot", sf::Color(138, 186, 243, 255), sf::Vector2f(800.0f, 440.0f)));
		window.draw(t.createtext("maze", sf::Color(138, 186, 243, 255), sf::Vector2f(750.0f, 470.0f)));

		//Menu Items
		sf::Text play = t.createtext("play", sf::Color(214, 238, 255, 255), sf::Vector2f(1200.0f, 370.0f));
		sf::Text about = t.createtext("about", sf::Color(214, 238, 255, 255), sf::Vector2f(1200.0f, 430.0f));
		sf::Text credits = t.createtext("credits", sf::Color(214, 238, 255, 255), sf::Vector2f(1200.0f, 490.0f));
		sf::Text exit = t.createtext("exit", sf::Color(214, 238, 255, 255), sf::Vector2f(1200.0f, 550.0f));

		window.draw(play);
		window.draw(about);
		window.draw(credits);
		window.draw(exit);

		auto mousepos = sf::Mouse::getPosition(window);
		auto translatedpos = window.mapPixelToCoords(mousepos);
		checkmouseover(play, translatedpos, window);
		checkmouseover(about, translatedpos, window);
		checkmouseover(credits, translatedpos, window);
		checkmouseover(exit, translatedpos, window);
	}
	else if (screenid == 1) { 
		credits(window);
	}
	else if (screenid == 2) { 
		puzzle(window);
	}
	else if (screenid == 3) {
		about(window);
	}
}

void Screens::puzzle(sf::RenderWindow& w)
{	
	lr->renderlevel(w) == 1 ? screenid = 0 : screenid = screenid;
}

void Screens::about(sf::RenderWindow& window)
{
	window.draw(t.createtext("Welcome to the Single-Shot Maze. It is a puzzle where you will be trying to solve all 14 mazes by moving the blue box to the red box", sf::Color(138, 186, 243, 255), sf::Vector2f(170.0f, 150.0f)));
	window.draw(t.createtext("within time and move limits. ", sf::Color(138, 186, 243, 255), sf::Vector2f(170.0f, 180.0f)));
	window.draw(t.createtext("The game will restart to maze 1 for you to try again whenever you are out of time or moves. Therefore, you need to finish ", sf::Color(138, 186, 243, 255), sf::Vector2f(170.0f, 250.0f)));
	window.draw(t.createtext("the game in one take. Here are all the controls you will need: ", sf::Color(138, 186, 243, 255), sf::Vector2f(170.0f, 290.0f)));
	window.draw(t.createtext("- To move the blue box, simply use the ", sf::Color(138, 186, 243, 255), sf::Vector2f(170.0f, 380.0f)));
	window.draw(t.createtext("ARROW KEYS.", sf::Color(217, 116, 116, 255), sf::Vector2f(680.0f, 380.0f)));
	window.draw(t.createtext("- At any moment of the game you can press                to reset.", sf::Color(138, 186, 243, 255), sf::Vector2f(170.0f, 440.0f)));
	window.draw(t.createtext("BACKSPACE", sf::Color(217, 116, 116, 255), sf::Vector2f(755.0f, 440.0f)));
	window.draw(t.createtext("- And you can use            to go back to menu.", sf::Color(138, 186, 243, 255), sf::Vector2f(170.0f, 500.0f)));
	window.draw(t.createtext("ESCAPE", sf::Color(217, 116, 116, 255), sf::Vector2f(425.0f, 500.0f)));
	window.draw(t.createtext("Have fun and see you at the maze ! ", sf::Color(138, 186, 243, 255), sf::Vector2f(170.0f, 600.0f)));
	
	sf::Text back = t.createtext("back", sf::Color(138, 186, 243, 255), sf::Vector2f(920.0f, 800.0f));
	window.draw(back);
	auto mousepos = sf::Mouse::getPosition(window);
	auto translatedpos = window.mapPixelToCoords(mousepos);
	checkmouseover(back, translatedpos, window);
}

void Screens::credits(sf::RenderWindow& w)
{
	w.clear();

	w.draw(t.createtext("Single-Shot Maze", sf::Color(138, 186, 243, 255), sf::Vector2f(845.0f, 100.f)));
	w.draw(t.createtext("Developer", sf::Color(138, 186, 243, 255), sf::Vector2f(885.0f, 200.f)));
	w.draw(t.createtext("Berkay Uckac", sf::Color(214, 238, 255, 255), sf::Vector2f(865.0f, 250.f)));
	w.draw(t.createtext("https://github.com/berkayuckac", sf::Color(214, 238, 255, 255), sf::Vector2f(780.0f, 300.f)));
	w.draw(t.createtext("Block Graphics", sf::Color(138, 186, 243, 255), sf::Vector2f(865.0f, 400.f)));
	w.draw(t.createtext("TinyWorlds - https://opengameart.org/content/colored-blocks-sketchy", sf::Color(214, 238, 255, 255), sf::Vector2f(550.0f, 450.f)));
	w.draw(t.createtext("Font Author", sf::Color(138, 186, 243, 255), sf::Vector2f(865.0f, 550.f)));
	w.draw(t.createtext("Kimberly Geswein  - https://fonts.google.com/specimen/Indie+Flower", sf::Color(214, 238, 255, 255), sf::Vector2f(550.0f, 600.f)));
	
	sf::Text back = t.createtext("back", sf::Color(138, 186, 243, 255), sf::Vector2f(920.0f, 800.f));
	w.draw(back);
	auto mousepos = sf::Mouse::getPosition(w);
	auto translatedpos = w.mapPixelToCoords(mousepos);
	checkmouseover(back, translatedpos, w);
}

void Screens::gotomenu(sf::RenderWindow& window)
{
	if (screenid == 0) {
		window.close();
	}
	else if (!(screenid == 0)) {
		screenid = 0;
		lr->reset_puzzle();
	}
}

void Screens::checkmouseover(sf::Text t1, sf::Vector2f translatedpos, sf::RenderWindow& wind) 
{
	if (t1.getGlobalBounds().contains(translatedpos)) {
		t1.setFillColor(sf::Color(217,116,116,255));
		wind.draw(t1);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			t1.setFillColor(sf::Color(196, 53, 53, 255));
			wind.draw(t1);
			if (t1.getString() == "credits") {
				screenid = 1;
			}
			else if (t1.getString() == "back") {
				screenid = 0;
			}
			else if (t1.getString() == "exit") {
				wind.close();
			}
			else if (t1.getString() == "play") {
				screenid = 2;
			}
			else if (t1.getString() == "about") {
				screenid = 3;
			}
		}
	}
	else {
		t1.setFillColor(sf::Color(214, 238, 255, 255));
	}
}