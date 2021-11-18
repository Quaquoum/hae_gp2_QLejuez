#include "turtle.hpp"

Turtle::Turtle(float posX, float posY) {

	//auto& head
	head = sf::CircleShape(6.f);
	body = sf::CircleShape(12.f);

	head.setFillColor(sf::Color::White);
	body.setFillColor(sf::Color::Green);

	body.setOrigin(body.getRadius(), body.getRadius());
	head.setOrigin(body.getOrigin());

	/*
	body.setPosition(posX,posY);
	head.setPosition(posX + 20,posY + 4);*/
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
	trs.rotate(rotat);
}

void Turtle::move(float speed)
{
	head.move(speed, 0);
	body.move(speed, 0);

	Cmd advance;
	advance.currentValue += speed;
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
	if (cmds->next != nullptr)
	{
		cmds->next = cmds;
	}
	else
	{
		appendCmds(cmds->next);
	}
	//ajouter a la fin de cmd
}

Cmd * Turtle::applyCmd(Cmd * cmd)
{
	//diminuer de current value
	//si fini renvoyer next et se supprimer

	return nullptr;
}
