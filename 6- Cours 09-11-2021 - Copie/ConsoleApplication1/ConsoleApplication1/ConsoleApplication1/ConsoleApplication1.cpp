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

	sf::RenderTexture turtleSprite;
	Turtle* turtle = new Turtle(1280 / 2, 720 / 2);
	//Turtle turtle(1280 / 2, 720 / 2);

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

		//rotate

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			turtle->rotate(2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			turtle->rotate(-2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			turtle->move(2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			turtle->move(-2);
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



		turtle->draw(window);

		window.display();

	}

	return 0;
}