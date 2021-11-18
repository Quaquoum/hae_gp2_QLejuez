#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Turtle {
public:
	sf::CircleShape head;
	sf::CircleShape body;

	bool alive = true;

	void draw(sf::RenderWindow& win);
};