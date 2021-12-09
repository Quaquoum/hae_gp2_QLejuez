#include <iostream>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "imconfig-SFML.h"
#include "imgui.h"
#include "imgui-SFML.h"

#include "Tool.hpp"
#include "Utility.hpp"

#include "Entity.hpp"
#include "Character.hpp"
#include "Game.hpp"
#include "world.hpp"

//EntityManager repo;

#pragma region Functions


#pragma endregion

int main()
{
#pragma region Variables

	//Window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Projet");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	//Load Font
	sf::Font font;
	font.loadFromFile("Game Of Squids.ttf");

	//Character
	sf::RectangleShape testChar(sf::Vector2f(100, 50));
	testChar.setPosition(100, 720 / 2);
	testChar.setOutlineThickness(3);

	testChar.setOutlineColor(sf::Color::Blue);

	/*sf::Texture texture;
	texture.loadFromFile("PlayerTexture");
	sf::Sprite character();
	*/


	Character* player = new Character();
	Character* wall = new Character();
	world world;

	wall->spr.setFillColor(sf::Color::Blue);
	bool initialized = false;


	//Mouse
	sf::CircleShape mouseShape(5.f);
	mouseShape.setFillColor(sf::Color::White);

	//Delta Time
	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	//imgui
	float tortuePenColor[3] = { (float)255 / 255,(float)255 / 255,(float)255 / 255 };
	float commandsnb = 0;

	sf::VertexArray grid(sf::Lines, 2 * (50));


	sf::CircleShape spr(8, 8);
	spr.setFillColor(sf::Color::Green);
	spr.setOutlineThickness(3);
	spr.setOutlineColor(sf::Color::Red);

	//Bord de la map
	

	//Entity* player = new Entity;
	//Character* player = new Character;

#pragma endregion
	sf::Clock deltaclock;

	while (window.isOpen())
	{

		//dt
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		
		sf::Time elapsed = deltaclock.getElapsedTime();
		deltaclock.restart();
		ImGui::SFML::Update(window, elapsed);

		//get mouse position
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		mouseShape.setPosition(mousePos.x, mousePos.y);

		if (!initialized)
		{
			player->setCoordinate(600, 600);
			//wall->setCoordinate(200, 200);
			wall->cx = 5;
			wall->cy = 5;
			wall->rx = 0;
			wall->ry = 0;

			world.initGrid();
			for (int i = 0; i < 1000; i++)
			{
				world.wallList[i] = nullptr;
			}


			initialized = true;
		}

#pragma region Controls

		player->update(dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player->move(-0.2f,0);
			//player->rx -= 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player->move(0.2f,0);
			//player.rx += 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player->move(0,-1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			//world.createWall(mousePos.x, mousePos.y);
			player->cx = 7;
			player->cy = 7;
			player->rx = 0;
			player->ry = 0;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			world.createWall(mousePos.x, mousePos.y);
			
		}
		
		int nb = 0;
		while (world.wallList[nb] != nullptr && nb < 1000)
		{
			player->collided(world.wallList[nb]);
			nb++;
		}

#pragma endregion

		sf::Event event;

#pragma region Imgui
		
		//imgui
		ImGui::Begin("Manager");
		ImGui::Text("Player");
		ImGui::Value("cx ", (int)player->cx);
		ImGui::SameLine();
		ImGui::Value(" cy ", (int)player->cy);
		ImGui::Value("rx ", (float)player->rx);
		ImGui::SameLine();
		ImGui::Value(" ry ", (float)player->ry);
		ImGui::Value("Friction X", (float)player->frictX);
		ImGui::Value("Friction Y", (float)player->frictY);
		ImGui::Text("Wall");
		ImGui::End();
		//4

#pragma endregion

		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			double dt = tEnterFrame - tExitFrame;
			if (event.type == sf::Event::Closed)
			window.close();
		}

		window.clear();
		window.draw(mouseShape);
		//window.draw(testChar);

		ImGui::SFML::Render(window);
		player->draw(window);
		wall->draw(window);
		world.drawGrid(window);
		world.drawWalls(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}