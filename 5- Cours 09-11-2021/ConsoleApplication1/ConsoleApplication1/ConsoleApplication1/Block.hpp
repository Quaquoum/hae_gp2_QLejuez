#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Block {
public:
	sf::RectangleShape b;

	bool alive = true;

	Block(float posX, float posY);

	void create(float posX, float posY);
	void update(double dt);
	void killed();

	void draw(sf::RenderWindow& win);
};