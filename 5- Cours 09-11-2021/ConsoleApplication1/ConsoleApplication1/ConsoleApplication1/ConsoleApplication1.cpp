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

EntityManager repo;

#pragma region Functions
void drawParticles(sf::RenderWindow& window, sf::CircleShape particles[])
{

	window.draw(particles[1]);
}

void drawMountain(sf::RenderWindow& window)
{
	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LinesStrip);
	sf::Color col = sf::Color::Green;

	sf::Vector2f a(0, 500);
	sf::Vector2f b(300, 300);
	sf::Vector2f c(900, 400);
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
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
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

void createBlocks(Block block)
{
	for (int i = 0; i < 2; i++)
	{
		float posY = 30 * i + 10;
		for (int j = 0; j < 16; j++)
		{
			float posX = 30 * j + 10;
			block.create(posX,posY);
		}
	}
}


#pragma endregion

int main()
{
#pragma region Variables

	//Window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "The Witcher 3");
	window.setVerticalSyncEnabled(true);
	sf::Vector2i windowPosition = window.getPosition();
	sf::View view(sf::Vector2f(1280/2, 720/2), sf::Vector2f(300.f, 200.f));
	view.setCenter(1280 / 2, 720 / 2);
	view.setSize(1280.f, 720.f);

	//Time
	sf::Clock clock;
	sf::Time time = sf::seconds(0.1f);

	//Block Array
	Block* block[30];

	//Sound
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("WallBounce.wav"))
		return -1;
	sf::Sound bounceSound;
	bounceSound.setBuffer(buffer);
	if (!buffer.loadFromFile("explosion.wav"))
		return -1;
	sf::Sound explodeSound;
	explodeSound.setBuffer(buffer);

	//Load Font
	sf::Font font;
	font.loadFromFile("Game Of Squids.ttf");

	//Pad
	sf::RectangleShape pad(sf::Vector2f(100, 20));
	pad.setFillColor(sf::Color::White);
	pad.setOutlineThickness(2);
	pad.setOutlineColor(sf::Color::Black);
	sf::Vector2f shapePosition = pad.getPosition();
	pad.setOrigin(580, 280);
	pad.setPosition(580, 630);
	sf::FloatRect playerHitbox = pad.getGlobalBounds();

	//Gun
	sf::RectangleShape gun(sf::Vector2f(70, 20));
	gun.setFillColor(sf::Color::Cyan);
	bool hasFired = false;

	//origin
	sf::CircleShape originShape(5.f);
	originShape.setFillColor(sf::Color::Blue);
	sf::Vector2f originPosition = pad.getOrigin();
	originShape.setPosition(originPosition);

	//Mouse
	sf::CircleShape mouseShape(5.f);
	mouseShape.setFillColor(sf::Color::White);

	//Bullet
	sf::CircleShape bullet(8.f);
	bullet.setFillColor(sf::Color(0, 0, 0, 0));
	bullet.setOutlineThickness(2);
	sf::FloatRect bulletHitbox = bullet.getGlobalBounds();

	sf::Vector2f bulletPos;
	int reversedx = 1;
	int reversedy = 1;

	//Background
	sf::Texture texture;
	texture.loadFromFile("Underwater texture.jpg", sf::IntRect(0, 0, 1280, 720));
	texture.setSmooth(true);
	sf::Sprite background;
	background.setTexture(texture);

	//Text
	sf::Text text("0", font);
	text.setPosition(10, 0);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Yellow);
	int score = 0;
	sf::String scoretext;

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	bool hasBeenCalled = false;
	bool brickAlternate = false;

	//test Collision
	float left1 = playerHitbox.left;
	float right1 = playerHitbox.left + playerHitbox.width;

#pragma endregion

	while (window.isOpen())
	{
		//Scale Background

		//create blocks
		if (hasBeenCalled == false)
		{
			for (int i = 0; i < 3; i++)
			{
				float posY = 100 * i + 60;
				for (int j = 0; j < 14; j++)
				{
					float posX = 90 * j + 60;
					Block* b = new Block(posX, posY);
					block[j + i*14] = b;
				}
			}
			hasBeenCalled = true;
		}

		//Check collisions
		bulletHitbox = bullet.getGlobalBounds();
		playerHitbox = pad.getGlobalBounds();

		bool touched = false;
		bool shake = false;
		for (int i = 0; i < 42; i++)
		{
			if (block[i]->alive == true && block[i]->collided(bulletHitbox))
			{
				explodeSound.play();
				block[i]->killed();
				score += 100;
				char numstr[10];
				//sprintf(numstr, "%i", score);
				scoretext = (to_string(score));
				text.setString(scoretext);
				touched = true;

				//Particles

				//ScreenShake
				/*for (int i = 0; i < 20; i++)
				{
					view.move(100 * rand(), 100 * rand());
					window.setView(view);
				}
				view.reset(sf::FloatRect(1280.f, 720.f, 300.f, 200.f));*/

			}
		}
		if (touched)
		{
			reversedy *= -1.1;
		}
		

		//get mouse position
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		mouseShape.setPosition(mousePos.x, mousePos.y);

		sf::Vector2f offset = pad.getPosition();
		offset.x -= mousePos.x;
		offset.y -= mousePos.y;

		auto pos = pad.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			pad.move(-5, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			pad.move(5, 0);
		}

		/*

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			shape.move(0, -5);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			shape.move(0, 5);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{

		}
		*/
	
		
		/*if (bullet.getPosition().x < 0 || bullet.getPosition().x > window.getSize().x || bullet.getPosition().y < 0 || bullet.getPosition().y > window.getSize().y)
		{
			
		}*/

		if (bullet.getFillColor() == sf::Color::Magenta)
		{
			//Move Bullet
			float projRad = 3.14 / 180 * bullet.getRotation();
            float x = 8.0f * cos(projRad);
            float y = 8.0f * sin(projRad);

			if ((bullet.getPosition().y < 0) || playerHitbox.intersects(bulletHitbox))
			{
				reversedy *= -1.1;
				bounceSound.play();
				//Get position de l'intersection
			}
			if ((bullet.getPosition().x < 0 || bullet.getPosition().x > window.getSize().x))
			{
				reversedx *= -1.9;
				bounceSound.play();
			}

			//collide with pad


			bullet.move(x * reversedx, y * reversedy);
		}
		

		//set Center
		pad.setOrigin(pad.getLocalBounds().width / 2.0f, pad.getLocalBounds().height / 2.0f);

		//rotate
		float angle = atan2(-offset.y, -offset.x) * (360 / (3.14 * 2));
		gun.setRotation(angle);
		gun.setPosition(pad.getPosition() + sf::Vector2f(0, 16));

		sf::Event event;
		while (window.pollEvent(event))
		{
			double dt = tEnterFrame - tExitFrame;
			if (event.type == sf::Event::Closed)
			window.close();

			//mouse gun
			if (event.type == sf::Event::MouseButtonPressed && !hasFired)
			{
				bullet.setPosition(gun.getPosition().x, gun.getPosition().y - 50);
				bullet.setRotation(gun.getRotation());
				bullet.setFillColor(sf::Color::Magenta);
				bullet.setOutlineColor(sf::Color::Black);
				hasFired = true;

			}
		}

		window.clear();
		window.draw(background);
		window.draw(pad);
		window.draw(text);
		window.draw(mouseShape);
		window.draw(bullet);
		//window.draw(gun);
		
		for (int i = 0; i < 42; i++)
		{
			if (block[i]->alive == true)
			{
				block[i]->draw(window);
			}
		}

		drawGround(window);
		drawMountain(window);
		window.display();

	}

	return 0;
}