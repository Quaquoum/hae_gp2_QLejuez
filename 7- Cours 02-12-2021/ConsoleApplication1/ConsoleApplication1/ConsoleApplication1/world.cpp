#include "world.hpp"

void world::createWall(int posX, int posY)
{
	Character* wall = new Character();
	wall->cx = (posX / 32);
	wall->cy = (posY / 32);
	wall->px = ((wall->cx + wall->rx) * 32);
	wall->py = ((wall->cy + wall->ry) * 32);
	/*
	wall->rx = (wall->px - wall->cx * 32) / 32;
	wall->ry = (wall->py - wall->cy * 32) / 32;

	if (wall->rx > 0.5)
	{
		wall->cx - 1;
	}
	if (wall->ry > 0.5)
	{
		wall->cy - 1;
	}
	wall->rx = 0;
	wall->ry = 0;
	*/

	wall->spr.setFillColor(sf::Color::Blue);
	

	
	int i = 0;

	while (wallList[i] != nullptr && i < 1000)
	{
		if (wallList[i]->cx == wall->cx && wallList[i]->cy == wall->cy)
		{
			return;
		}
		i++;
	}
	wall->spr.setPosition(wall->px, wall->py);
	wallList[i] = wall;

}

void world::drawWalls(sf::RenderWindow& win)
{
	int i = 0;

	while(wallList[i] != nullptr && i < 1000)
	{
		win.draw(wallList[i]->spr);
		i++;
	}
}


void world::initGrid()
{
	gridRct = sf::RectangleShape(sf::Vector2f(stride, stride));
	gridRct.setOutlineColor(sf::Color::White);
	gridRct.setOutlineThickness(0.9f);
	gridRct.setFillColor(sf::Color::Transparent);
	gridRct.setOrigin(stride / 2, stride / 2);
}
void world::drawGrid(sf::RenderWindow& win)
{
	for (int y = 0; y < gridSize.y * stride; y += stride)
	{
		for (int x = 0; x < gridSize.x * stride; x += stride)
		{
			gridRct.setPosition(x + stride, y + stride);
			win.draw(gridRct);
		}
	}
}