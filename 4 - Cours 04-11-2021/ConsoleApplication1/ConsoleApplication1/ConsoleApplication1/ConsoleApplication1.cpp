// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tool.hpp"
#include "Utility.hpp"
//#include "Bullet.hpp"

void drawParticles(sf::RenderWindow& window, sf::CircleShape particles[])
{
	

	window.draw(particles[1]);
}

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

	//Gun
	sf::RectangleShape gun(sf::Vector2f(70, 20));
	gun.setFillColor(sf::Color::Cyan);

	//origin
	sf::CircleShape originShape(5.f);
	originShape.setFillColor(sf::Color::Blue);
	sf::Vector2f originPosition = shape.getOrigin();
	originShape.setPosition(originPosition);

	//Mouse
	sf::CircleShape mouseShape(5.f);
	mouseShape.setFillColor(sf::Color::White);

	//Bullet
	sf::CircleShape bullet(10.f);
	bullet.setFillColor(sf::Color(0,0,0,0));
	sf::Vector2f bulletPos;

	//Text
	sf::Text text("hello", font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Yellow);

	//particles
	sf::CircleShape particles[]
	{
		sf::CircleShape(1),
		sf::CircleShape(1),
		sf::CircleShape(1),
		sf::CircleShape(1)
	};

	sf::CircleShape particle(5.f);
	particle.setFillColor(sf::Color::White);

	int fade = 0;
	int randline;


	//floor
	/*
	sf::VertexArray floor(sf::LinesStrip, 2);
	floor[0].position = sf::Vector2f(0, 710);
	floor[1].position = sf::Vector2f(1280, 710);
	*/
	


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

		auto pos = shape.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			shape.move(-5, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			shape.move(5, 0);
		}

		/* up & down 58
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			shape.move(0, -5);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			shape.move(0, 5);
		}
		*/
		
		if (bullet.getPosition().x < 0 || bullet.getPosition().x > window.getSize().x || bullet.getPosition().y < 0 || bullet.getPosition().y > window.getSize().y)
		{
			bullet.setFillColor(sf::Color(0, 0, 0, 0));
		}

		if (bullet.getFillColor() == sf::Color::Magenta)
		{
			//Move Bullet
			float projRad = 3.14 / 180 * bullet.getRotation();
            float x = 10.0f * cos(projRad);
            float y = 10.0f * sin(projRad);
            bullet.move(x, y);

		}
		

		//set Center
		shape.setOrigin(shape.getLocalBounds().width / 2.0f, shape.getLocalBounds().height / 2.0f);

		//rotate
		float angle = atan2(-offset.y, -offset.x) * (360 / (3.14 * 2));
		gun.setRotation(angle);
		gun.setPosition(shape.getPosition() + sf::Vector2f(0, 16));

		if (fade > 0)
		{
			fade -= 3;
			particle.setFillColor(sf::Color(255, 0, 0, fade));

			//move
			float projRad = 3.14 / 180 * particle.getRotation();
			float x = 2.0f * cos(projRad);
			float y = 2.0f * sin(projRad);
			particle.move(x, y);
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			double dt = tEnterFrame - tExitFrame;
			if (event.type == sf::Event::Closed)
			window.close();

			//sf::Vector2f mousePoss = sf::Vector2f

			//mouse gun
			if (event.type == sf::Event::MouseButtonPressed)
			{
				/*auto pos = gun.getPosition();
				auto dir = mousePos - pos;
				float dirlen = std::sqrt(dir.x * dir.x + dir.y* dir.y);
				sf::Vector
				bullets.create(pos.x,pos.y)*/

				bullet.setPosition(gun.getPosition());
				bullet.setRotation(gun.getRotation());
				bullet.setFillColor(sf::Color::Magenta); //change to white once it's good

				randline = rand() % 30;
				particle.setPosition(bullet.getPosition());
				particle.setRotation(gun.getRotation() + randline);

				fade = 255;

			}
		}

		window.clear();
		window.draw(shape);
		window.draw(text);
		window.draw(mouseShape);
		window.draw(bullet);
		window.draw(gun);
		window.draw(particle);

		drawGround(window);
		drawMountain(window);

		window.display();
	}

	return 0;
}