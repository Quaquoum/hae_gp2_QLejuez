#pragma once

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
	float originalValue = 0.0f;
	float currentValue = 0.0f;
	Cmd* next = nullptr;

};

class Turtle : public sf::Transform
{
public:
	Turtle(float posX, float posY);

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

	//ajoute les cmds a la fin de la liste courante
	void appendCmds(Cmd* cmds);

protected:
	Cmd* applyCmd(Cmd* cmd);
	Cmd* cmds = nullptr;
};