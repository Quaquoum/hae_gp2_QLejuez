// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tool.hpp"
#include "Utility.hpp"
//#include "Bullet.hpp"
#include "Entity.hpp"
#include <SFML/Audio.hpp>
#include "Block.hpp"
#include "turtle.hpp"

EntityManager repo;

#pragma region Functions


#pragma endregion

int main()
{
#pragma region Variables

	//Window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Turtle Adventure");
	window.setVerticalSyncEnabled(true);

	//Block Array
	Block* block[30];

	Turtle* turtle;

	//Load Font
	sf::Font font;
	font.loadFromFile("Game Of Squids.ttf");

	//Mouse
	sf::CircleShape mouseShape(5.f);
	mouseShape.setFillColor(sf::Color::White);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

#pragma endregion

	while (window.isOpen())
	{
		//get mouse position
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		mouseShape.setPosition(mousePos.x, mousePos.y);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			
		}
	
		sf::Event event;
		while (window.pollEvent(event))
		{
			double dt = tEnterFrame - tExitFrame;
			if (event.type == sf::Event::Closed)
			window.close();
		}

		window.clear();
		window.draw(mouseShape);
		window.draw(turtle);

		window.display();

	}

	return 0;
}