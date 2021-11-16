#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Block {
public:
	sf::RectangleShape b;

	std::vector<float>	posX;
	std::vector<float>	posY;

	std::vector<bool>	alive;

	Block();

	void create(float posX, float posY);
	void update(double dt);

	void draw(sf::RenderWindow& win);
};