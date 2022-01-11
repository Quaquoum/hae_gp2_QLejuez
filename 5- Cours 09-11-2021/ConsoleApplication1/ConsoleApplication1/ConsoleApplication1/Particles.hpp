#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Particles {
public:
	sf::RectangleShape b;
	bool alive = false;

	//float px;
	//float py;
	float moveX;
	float moveY;
	Particles(sf::Vector2f pos);

	void update(double dt);
	void blockdeath(sf::Vector2f pos,float X, float Y);

	void draw(sf::RenderWindow& win);
};