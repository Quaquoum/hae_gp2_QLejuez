#include <iostream>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include "Tool.hpp"
#include "Utility.hpp"
//#include "Bullet.hpp"
#include "Entity.hpp"
#include <SFML/Audio.hpp>
#include "Block.hpp"
#include "turtle.hpp"
#include "CommandList.hpp"


#include "imconfig-SFML.h"
#include "imgui.h"
#include "imgui-SFML.h"

EntityManager repo;

#pragma region Functions


#pragma endregion

int main()
{
#pragma region Variables

	//Window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Turtle Adventure");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	//Load Font
	sf::Font font;
	font.loadFromFile("Game Of Squids.ttf");

	//Character
	sf::Sprite character();


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




#pragma endregion
	sf::Clock deltaclock;

	while (window.isOpen())
	{

		//dt
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();

		//get mouse position
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		mouseShape.setPosition(mousePos.x, mousePos.y);


#pragma region Controls

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
		}

#pragma endregion

		sf::Event event;

#pragma region Imgui
		/*
		//imgui
		ImGui::SFML::Update(window, deltaclock.restart());
		bool toolActive;
		ImGui::Begin("Command Panel", &toolActive, ImGuiWindowFlags_MenuBar);
		ImGui::Columns(2, "locations");
		ImGui::SetColumnWidth(0,200);
		ImGui::End();
		*/

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

		//ImGui::SFML::Render(window);

		window.display();
	}

	//ImGui::SFML::Shutdown();
	return 0;
}