#pragma once

#include "CommandList.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"

enum CmdType
{
	Advance,
	Turn,
	PenUp,
	PenDown,
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

	Cmd(CmdType t)
	{
		type = t;
		//originalValue = value;
	}

	Cmd*append(Cmd*nu)
	{
		if (next == nullptr)
			next = nu;
		else
			next->append(nu);
		return this;
	}

};

class Turtle : public sf::Transform
{
public:
	Turtle(float posX, float posY);

	Cmd* cmdList[100];

	sf::CircleShape head;
	sf::CircleShape body;
	sf::CircleShape drawshape;

	sf::Transform trs;
	sf::CircleShape* comps[3];

	bool alive = true;
	sf::Vector2f headOffset;

	sf::RenderTexture* turtleTexture = nullptr;
	sf::RenderTexture* drawTexture = nullptr;
	//sf::Texture texture;

	sf::Color penColor;
	sf::Sprite sprite;
	bool penOn = false;
	

	void drawOn();
	void drawOff();
	void changeColor();

	void update(double dt);
	void rotate(float rot);
	void move(sf::Vector2f direction);
	void draw(sf::RenderWindow& win);
	void changeColor(sf::Color color);
	
	void setCmds(Cmd* cmds);

	Cmd* createCmd(float oValue, float curValue, CmdType ctype);
	//ajoute les cmds a la fin de la liste courante
	void appendCmds(Cmd* cmds);
	void printCommandList();

protected:
	Cmd* applyCmd(Cmd* cmd, float dt);
	Cmd* cmds = nullptr;
};