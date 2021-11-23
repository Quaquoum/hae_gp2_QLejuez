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
#include "CommandList.hpp"

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
	Turtle turtle = Turtle(500, 600);
	Turtle* GV_turtle = &turtle;

	//Load Font
	sf::Font font;
	font.loadFromFile("Game Of Squids.ttf");

	//Mouse
	sf::CircleShape mouseShape(5.f);
	mouseShape.setFillColor(sf::Color::White);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();
	CommandList* cmd1 = new CommandList(CommandList::CommandType::Advance, 1);

	for (int i = 1; i < 10; i++)
	{
		Cmd* adv = GV_turtle->createCmd(1, 10, Advance);
		
		GV_turtle->appendCmds(adv);
	}
	GV_turtle->printCommandList();

#pragma endregion

	while (window.isOpen())
	{
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();

		//get mouse position
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		mouseShape.setPosition(mousePos.x, mousePos.y);

		//rotate

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			GV_turtle->rotate(2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			GV_turtle->rotate(-2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			GV_turtle->move(sf::Vector2f(5, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			GV_turtle->move(sf::Vector2f(-5, 0));
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



		GV_turtle->draw(window);

		window.display();

	}

	return 0;
}