#include "turtle.hpp"
#include "Tool.hpp"

Turtle::Turtle(float posX, float posY) {

	trs = Transform();

	//auto& head
	head = sf::CircleShape(6.f);
	body = sf::CircleShape(12.f);

	head.setFillColor(sf::Color::White);
	body.setFillColor(sf::Color::Green);

	body.setOrigin(body.getRadius(), body.getRadius());
	head.setOrigin(body.getRadius() - 20, body.getRadius() - 5);

	headOffset = sf::Vector2f(body.getRadius() + 10, body.getRadius() / 2);

	/*
	body.setPosition(posX,posY);
	head.setPosition(posX + 20,posY + 4);*/
	
	this->trs.translate(posX,posY);
}

void Turtle::drawOn(sf::RenderWindow & win)
{
}

void Turtle::drawOff(sf::RenderWindow & win)
{
}

void Turtle::changeColor()
{
}

void Turtle::update(double dt)
{
}

void Turtle::rotate(float rotat)
{
	this->trs.rotate(rotat);
}

void Turtle::move(sf::Vector2f direction)
{
	trs.translate(direction);
}

void Turtle::draw(sf::RenderWindow & win)
{
	if (this == nullptr)
		return;

	//for (auto& c : comps)
		//win.draw(c, trs);

	win.draw(head, trs);
	win.draw(body, trs);
}

void Turtle::appendCmds(Cmd * cmds)
{
	int i = 0;
	while (cmdList[i] != nullptr && i < 100)
	{
		i++;
	}
	if (i < 100)
	{
		cmdList[i] = cmds;
	}
	//ajouter a la fin de cmd
}

void Turtle::printCommandList()
{
	int i = 0;
	while (cmdList[i] != nullptr && i < 100)
	{
		printf("%i : %i \n", i, cmdList[i]->currentValue);

		i++;
	}
}

Cmd * Turtle::applyCmd(Cmd * cmd, float dt)
{
	if (cmd == nullptr)
		return nullptr;
	//diminuer de current value

	if (cmd->originalValue > 0)
	{
		cmd->currentValue -= dt;
		if (cmd->currentValue <= 0)
			return applyCmd(cmd->next, dt);
	}
	else
	{
		cmd->currentValue += dt;
		if (cmd->currentValue <= 0)
			return applyCmd(cmd->next, dt);
	}

	if (cmd->type == Advance)
	{
		move(sf::Vector2f(cmd->originalValue, 0));
	}
	if (cmd->type == Turn)
	{
		rotate(cmd->originalValue);
	}

	//si fini renvoyer next et se supprimer

	return applyCmd(cmd, dt);
}

Cmd* Turtle::createCmd(float oValue, float curValue, CmdType ctype)
{
	Cmd* cmds = new Cmd;
	cmds->originalValue = oValue;
	cmds->currentValue = curValue;
	cmds->type = ctype;

	return cmds;
}
