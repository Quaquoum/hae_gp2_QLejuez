// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tool.hpp"

int main()
{
	//Load Font
	sf::Font font;
	font.loadFromFile("Game Of Squids.ttf");

	//Shape
	sf::RenderWindow window(sf::VideoMode(1280, 720), "The Witcher 3");
	window.setVerticalSyncEnabled(true);
	sf::RectangleShape shape(sf::Vector2f(100, 50));
	shape.setFillColor(sf::Color::Red);
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color::White);
	sf::Vector2f shapePosition = shape.getPosition();
	shape.setOrigin(580,280);
	shape.setPosition(580, 280);

	//origin
	sf::CircleShape originShape(5.f);
	originShape.setFillColor(sf::Color::Blue);
	sf::Vector2f originPosition = shape.getOrigin();
	originShape.setPosition(originPosition);

	//Mouse
	sf::CircleShape mouseShape(5.f);
	mouseShape.setFillColor(sf::Color::White);

	//Text
	sf::Text text("hello", font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Yellow);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	while (window.isOpen())
	{

		//get mouse position
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		mouseShape.setPosition(mousePos.x, mousePos.y);

		sf::Vector2f offset = shape.getPosition();
		offset.x -= mousePos.x;
		offset.y -= mousePos.y;

		sf::Event event;
		while (window.pollEvent(event))
		{
			double dt = tEnterFrame - tExitFrame;
			if (event.type == sf::Event::Closed)
			window.close();

			auto pos = shape.getPosition();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				shape.move(-1,0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				shape.move(1, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				shape.move(0, -1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				shape.move(0, 1);
			}
			
			//set Center
			shape.setOrigin(shape.getLocalBounds().width / 2.0f, shape.getLocalBounds().height / 2.0f);

			//rotate
			float angle = atan2(-offset.y, -offset.x) * (360 / (3.14 * 2));
			shape.setRotation(angle);

		}

		window.clear();
		window.draw(shape);
		window.draw(text);
		window.draw(mouseShape);
		window.display();
	}

	return 0;
}