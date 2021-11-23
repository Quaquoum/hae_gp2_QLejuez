#pragma once

#include "CommandList.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"

enum CmdType
{
	Advance,
	Turn,
};

struct Cmd
{
	CmdType type = Advance;
	//Original value = direction
	float originalValue = 0.0f;
	//currentvalue = time passed on an action
	float currentValue = 0.0f;
	Cmd* next = nullptr;
	Cmd* head = nullptr;

public:
	

};

class Turtle : public sf::Transform
{
public:
	Turtle(float posX, float posY);

	Cmd* cmdList[100];

	sf::CircleShape head;
	sf::CircleShape body;
	sf::Transform trs;
	sf::CircleShape* comps[3];

	bool alive = true;
	sf::Vector2f headOffset;
	
	void drawOn(sf::RenderWindow& win);
	void drawOff(sf::RenderWindow& win);
	void changeColor();

	void update(double dt);
	void rotate(float rot);
	void move(sf::Vector2f direction);
	void draw(sf::RenderWindow& win);

	void setCmds(Cmd* cmds);

	Cmd* createCmd(float oValue, float curValue, CmdType ctype);
	//ajoute les cmds a la fin de la liste courante
	void appendCmds(Cmd* cmds);
	void printCommandList();

protected:
	Cmd* applyCmd(Cmd* cmd, float dt);
	Cmd* cmds = nullptr;
};