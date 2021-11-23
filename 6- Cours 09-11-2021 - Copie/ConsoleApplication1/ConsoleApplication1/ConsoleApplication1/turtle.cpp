#include "turtle.hpp"
#include "Tool.hpp"

Turtle::Turtle(float posX, float posY) {

	trs = Transform();

	//auto& head
	head = sf::CircleShape(6.f);
	body = sf::CircleShape(12.f);
	drawshape = sf::CircleShape(6.f);

	head.setFillColor(sf::Color::White);
	body.setFillColor(sf::Color::Green);
	drawshape.setFillColor(sf::Color::Blue);

	body.setOrigin(body.getRadius(), body.getRadius());
	drawshape.setOrigin(body.getRadius(), body.getRadius());
	head.setOrigin(body.getRadius() - 20, body.getRadius() - 5);

	headOffset = sf::Vector2f(body.getRadius() + 10, body.getRadius() / 2);

	/*
	body.setPosition(posX,posY);
	head.setPosition(posX + 20,posY + 4);*/
	turtleTexture = new sf::RenderTexture();
	turtleTexture->create(2048, 2048);

	this->trs.translate(posX,posY);
}

void Turtle::update(double dt)
{
}

void Turtle::rotate(float rotat, double dt)
{
	this->trs.rotate(rotat);
}

void Turtle::rotateCmd(float rot, double dt)
{

}

void Turtle::move(float distance, double dt, float speed)
{
	trs.translate(distance,0);
}

void Turtle::moveCmd(float distance, double dt, float speed)
{
}

void Turtle::draw(sf::RenderWindow & win)
{
	if (this == nullptr)
		return;

	//for (auto& c : comps)
		//win.draw(c, trs);
	if (penOn)
	{
		turtleTexture->draw(drawshape, trs);
	}
	turtleTexture->display();

	sf::Sprite sprite(turtleTexture->getTexture());
	win.draw(sprite);
	win.draw(head, trs);
	win.draw(body, trs);
}

void Turtle::changeColor(sf::Color color)
{
	drawshape.setFillColor(color);
}

void Turtle::appendCmds(Cmd * cmd)
{
	if (cmds)
	{
		cmds = cmds->append(cmd);
	}
	else
	{
		cmds = cmd;
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
	switch (cmd->type)
	{
	case Advance: 
		trs.translate(0, cmd->originalValue); 
		//if (penOn)
		break;

	case Turn: trs.rotate(cmd->originalValue); break; break;
	case PenUp: penOn = true; break;
	case PenDown: penOn = false; break;
	default:
		break;
	}
	return nullptr;
}

/*Cmd* Turtle::createCmd(float oValue, float curValue, CmdType ctype)
{
	Cmd* cmds;
	return cmds;
}*/

void Turtle::drawOn()
{
	penOn = true;
}

void Turtle::drawOff()
{
	penOn = false;

}
