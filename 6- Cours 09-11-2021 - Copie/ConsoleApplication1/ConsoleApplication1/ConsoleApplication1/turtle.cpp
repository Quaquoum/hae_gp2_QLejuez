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
