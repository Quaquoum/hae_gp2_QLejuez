#include "Particles.hpp"

Particles::Particles(sf::Vector2f pos)
{
	int length = 10;
	int height = 10;
	b = sf::RectangleShape(sf::Vector2f(length, height));
	b.setOutlineThickness(2);
	b.setFillColor(sf::Color(209, 0, 0, 255));
	b.setOutlineColor(sf::Color::Black);
	b.setOrigin(sf::Vector2f(length / 2, height / 2));
	b.setPosition(pos);
}

void Particles::update(double dt)
{
	if (alive)
	{
		b.move((moveX - 1) * 1.5, (moveY - 1) * 1.5);
		b.scale(0.95f, 0.95f);
		if (b.getScale().x < 0.1)
		{
			alive = false;
			b.setScale(1, 1);
		}
	}
}

void Particles::blockdeath(sf::Vector2f pos, float X, float Y)
{
	moveX = X;
	moveY = Y;
	b.setPosition(pos);
	alive = true;
}

void Particles::draw(sf::RenderWindow & win)
{
	if (this == nullptr)
		return;

	if (alive)
	{
		win.draw(b);
	}
}
