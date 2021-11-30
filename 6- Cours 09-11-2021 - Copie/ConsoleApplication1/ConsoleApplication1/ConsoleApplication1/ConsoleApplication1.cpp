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
						GV_turtle->move(nb,dt);
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

#pragma region Imgui
		//imgui
		ImGui::SFML::Update(window, deltaclock.restart());
		bool toolActive;
		ImGui::Begin("Command Panel", &toolActive, ImGuiWindowFlags_MenuBar);
		ImGui::Text("Commands :");
		ImGui::Columns(2, "locations");

		ImGui::SetColumnWidth(0,200);

		if (ImGui::Button("Advance", ImVec2(200, 20)))
		{
			GV_turtle->move(5, dt);
		}
		if (ImGui::Button("back", ImVec2(200, 20)))
		{
			GV_turtle->move(-5, dt);
		}
		if (ImGui::Button("left", ImVec2(200, 20)))
		{
			GV_turtle->rotate(-8, dt);
		}
		if (ImGui::Button("right", ImVec2(200, 20)))
		{
			GV_turtle->rotate(8, dt);
		}
		ImGui::NextColumn();
		if (ImGui::Button("Draw", ImVec2(200, 20)))
		{
			GV_turtle->drawOn();
		}
		if (ImGui::Button("Stop Drawing", ImVec2(200, 20)))
		{
			GV_turtle->drawOff();
		}
		if (ImGui::ColorEdit3("color", tortuePenColor))
		{
			sf::Color penColor;
			penColor.r = tortuePenColor[0] * 255;
			penColor.g = tortuePenColor[1] * 255;
			penColor.b = tortuePenColor[2] * 255;
			GV_turtle->changeColor(penColor);
		}
		ImGui::Text("Commands :");

		static Cmd* head = nullptr;

		if (ImGui::Button("+"))
		{
			auto p = new Cmd(Advance);
			p->originalValue = p->currentValue = 5;
			if (nullptr == head)
			{
				head = p;
			}
			else
				head = head->append(p);
		}

		int idx = 0;
		ImGui::Separator();
		auto h = head;
		while (h)
		{
			ImGui::PushID(idx);
			ImGui::Value("idx", idx);
			//combo pour changer la commande
			static const char* items[] =
			{
			"Advance",
			"Turn",
			"PenUp",
			"PenDown",
			"PenColor",
			};

			ImGui::Combo("Cmd Type", (int*)&h->type, items, IM_ARRAYSIZE(items));

			switch (h->type)
			{
			case CmdType::Clear:
			case PenDown:
			case PenUp:
				break;
			case PenColor:
				if (ImGui::ColorEdit3("color", tortuePenColor))
				{
					sf::Color Col;
					Col.r = tortuePenColor[0] * 255;
					Col.g = tortuePenColor[1] * 255;
					Col.b = tortuePenColor[2] * 255;
				}
				break;

			default:
				ImGui::DragFloat("value", &h->originalValue);
				break;
			}
			


			ImGui::NewLine();
			ImGui::Separator();
			h = h->next;
			idx++;
			ImGui::PopID();
		}

		if (ImGui::Button("Run"))
		{
			if (head)
			{
				GV_turtle->appendCmds(h);
			}
		}


		ImGui::SameLine();
		
		if (ImGui::Button("Load"))
		{

		}

		ImGui::SameLine();

		if (ImGui::Button("Save"))
		{
			FILE* fp = nullptr;
			fopen_s(&fp, "cmd.txt", "rb");

		}

		ImGui::End();
#pragma endregion

		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			double dt = tEnterFrame - tExitFrame;
			if (event.type == sf::Event::Closed)
			window.close();
		}


		window.clear();
		window.draw(lines);
		window.draw(mouseShape);

		GV_turtle->draw(window);


		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}