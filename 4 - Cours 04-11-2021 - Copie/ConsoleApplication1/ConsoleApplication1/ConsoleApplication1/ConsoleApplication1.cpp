// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{


	sf::Font font;
	font.loadFromFile("Game Of Squids.ttf");

	sf::RenderWindow window(sf::VideoMode(1280, 720), "The Witcher 3");
	window.setVerticalSyncEnabled(true);
	sf::RectangleShape shape(sf::Vector2f(100, 50));
	shape.setFillColor(sf::Color::Red);
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color::White);


	sf::Text text("hello", font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Yellow);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();

			auto pos = shape.getPosition();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				pos.x--;
				shape.setPosition(pos);
				//shape.move(-1,0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				pos.x++;
				shape.setPosition(pos);
				//shape.move(1, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				pos.y--;
				shape.setPosition(pos);
				//shape.move(0, -1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				pos.y++;
				shape.setPosition(pos);
				//shape.move(0, 1);
			}
			
		}

		window.clear();
		window.draw(shape);
		window.draw(text);
		window.display();
	}

	return 0;
}