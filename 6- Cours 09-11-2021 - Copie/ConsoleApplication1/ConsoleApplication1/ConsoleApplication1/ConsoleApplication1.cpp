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

	sf::RenderTexture turtleSprite;
	Turtle turtle = Turtle(500, 600);
	Turtle* GV_turtle = &turtle;

	//Load Font
	sf::Font font;
	font.loadFromFile("Game Of Squids.ttf");

	//Mouse
	sf::CircleShape mouseShape(5.f);
	mouseShape.setFillColor(sf::Color::White);

	//Lines
	sf::VertexArray lines(sf::LineStrip, 100);
	int linesidx = 0;


	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();
	CommandList* cmd1 = new CommandList(CommandList::CommandType::Advance, 1);



#pragma endregion

	while (window.isOpen())
	{
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();

		//get mouse position
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		mouseShape.setPosition(mousePos.x, mousePos.y);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			GV_turtle->rotate(-2,dt);
			//GV_turtle->appendCmds(new Cmd,rotate(2))
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			GV_turtle->rotate(2,dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			GV_turtle->move(5,dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			GV_turtle->move(-5,dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			GV_turtle->drawOn();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			GV_turtle->drawOff();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			GV_turtle->changeColor(sf::Color::Blue);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			GV_turtle->changeColor(sf::Color::Red);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			GV_turtle->changeColor(sf::Color::Yellow);
		}


		static bool APressed = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			FILE* fp = nullptr;
			fopen_s(&fp, "cmd.txt", "rb");

			if (fp && !feof(fp))
			{
				char line[256] = {};
				for (;;)
				{
					int64_t nb = 0;
					fscanf_s(fp, "%s %lld \n", line, 256, &nb);
					std::string s = line;
					if (s == "Advance")
					{
						GV_turtle->moveCmd(nb,dt);
					}
					if (s == "Rotate")
					{
						GV_turtle->rotate(nb,dt);
					}
					if (s == "PenUp")
					{
						GV_turtle->drawOn();
					}
					if (s == "PenDown")
					{
						GV_turtle->drawOff();
					}
					if (s == "PenColor")
					{
						GV_turtle->changeColor(sf::Color((unsigned int)nb));
					}
					if (feof(fp))
					{
						break;
					}
				}
				fclose(fp);
			}
			APressed = true;
		}
		APressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);

		sf::Event event;
		while (window.pollEvent(event))
		{
			double dt = tEnterFrame - tExitFrame;
			if (event.type == sf::Event::Closed)
			window.close();
		}

		window.clear();
		window.draw(lines);
		//window.draw(mouseShape);

		GV_turtle->draw(window);

		window.display();

	}

	return 0;
}