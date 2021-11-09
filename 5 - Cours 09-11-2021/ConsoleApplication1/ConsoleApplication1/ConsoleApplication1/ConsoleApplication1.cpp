// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tool.hpp"
#include "Utility.hpp"
//#include "Bullet.hpp"

void drawMountain(sf::RenderWindow& window)
{
	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LinesStrip);
	sf::Color col = sf::Color::Green;

	sf::Vector2f a(0,500);
	sf::Vector2f b(300,300);
	sf::Vector2f c(900,400);
	sf::Vector2f d(window.getSize().x, 500);

	for (int i = 0; i < 256; i++)
	{
		float t = 1.0f * i / 256;
		//float x = (window.getSize().x - 0) * i / 255;
		float x = catmull(a.x, a.x, b.x, c.x, t);
		float y = catmull(a.y, a.y, b.y, c.y, t);
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
	}

	for (int i = 0; i < 256; i++)
	{
		float t = 1.0f * i / 256;
		//float x = (window.getSize().x - 0) * i / 255;
		float x = catmull(a.x, b.x, c.x, d.x, t);
		float y = catmull(a.y, b.y, c.y, d.y, t);
		arr.append(sf::Vertex(sf::Vector2f(x,y), col));
	}

	for (int i = 0; i < 256; i++)
	{
		float t = 1.0f * i / 256;
		//float x = (window.getSize().x - 0) * i / 255;
		float x = catmull(b.x, c.x, d.x, d.x, t);
		float y = catmull(b.y, c.y, d.y, d.y, t);
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
	}
	/*
	arr.append(sf::Vertex(a, col));
	arr.append(sf::Vertex(b, col));
	arr.append(sf::Vertex(c, col));
	arr.append(sf::Vertex(d, col));
	*/

	window.draw(arr);
}

void drawGround(sf::RenderWindow& window)
{
	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LinesStrip);
	sf::Color col = sf::Color::Yellow;

	float baseline = 600 + 32;
	sf::Vector2f a(0, baseline);
	sf::Vector2f b(window.getSize().x, baseline);

	arr.append(sf::Vertex(a, col));
	arr.append(sf::Vertex(b, col));

	window.draw(arr);
}

int main()
{

	//Load Font
	sf::Font font;
	font.loadFromFile("Game Of Squids.ttf");

	//Shape
	sf::RenderWindow window(sf::VideoMode(1280, 720), "The Witcher 3");
	window.setVerticalSyncEnabled(true);

	sf::RectangleShape shape(sf::Vector2f(50, 100));
	shape.setFillColor(sf::Color::Red);
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color::White);
	sf::Vector2f shapePosition = shape.getPosition();
	shape.setOrigin(580,280);
	shape.setPosition(580, 580);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	while (window.isOpen())
	{

		auto pos = shape.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			shape.move(-5, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			shape.move(5, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			shape.move(0, -5);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			shape.move(0, 5);
		}
		
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			double dt = tEnterFrame - tExitFrame;
			if (event.type == sf::Event::Closed)
			window.close();

		}

		window.clear();
		window.draw(shape);

		drawGround(window);
		drawMountain(window);

		window.display();
	}

	return 0;
}