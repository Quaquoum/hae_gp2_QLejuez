#pragma once

#include "Character.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class world {
public:
	Character* wallList[1000];

	void createWall(int posX, int posY);

	sf::RectangleShape gridRct;
	sf::Vector2f gridSize = { 25,25 };

	int stride = 32;

	void drawWalls(sf::RenderWindow& win);
	void drawGrid(sf::RenderWindow& win);
	void initGrid();
};