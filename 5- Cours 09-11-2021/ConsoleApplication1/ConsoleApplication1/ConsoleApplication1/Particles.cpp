#include "Particles.hpp"

Particles::Particles(sf::Vector2f pos)
{
	int length = 20;
	int height = 20;
	b = sf::RectangleShape(sf::Vector2f(length, height));
	b.setOutlineThickness(2);
	b.setFillColor(sf::Color(209, 0, 0, 255));
	b.setOutlineColor(sf::Color::Black);
	b.setOrigin(sf::Vector2f(length / 2, height / 2));
	b.setPosition(pos);
}

void Particles::update(double dt,float rot)
{
	b.setRotation(rot);
	b.move(1, 0);
}
