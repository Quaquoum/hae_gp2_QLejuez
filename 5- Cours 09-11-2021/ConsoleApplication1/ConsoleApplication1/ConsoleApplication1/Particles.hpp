#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Particles {
public:
	sf::RectangleShape b;
	bool alive = true;

	//float px;
	//float py;

	Particles(sf::Vector2f pos);

	void update(double dt, float rot);

	void draw(sf::RenderWindow& win);
};