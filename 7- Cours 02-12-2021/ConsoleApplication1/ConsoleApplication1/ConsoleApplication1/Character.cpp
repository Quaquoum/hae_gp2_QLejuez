#include "Character.hpp"


Character::Character()
{
	spr.setSize(sf::Vector2f(sf::Vector2f(32, 32)));
	spr.setFillColor(sf::Color::Green);
	spr.setOutlineThickness(3);
	spr.setOutlineColor(sf::Color::Red);
	spr.setOrigin(spr.getSize().x * 0.5f, spr.getSize().y * 0.5);

	cx = 10;
	cy = 10;
	rx = 0;
	ry = 0;
}

void Character::syncSprite()
{
}

void Character::update(double dt)
{
	//Movement
	ry += dy;
	rx += dx;
	dx *= 0.60;
	dy *= 0.90;

	while (rx > 1) { 
		rx--;	
		cx++; 
	}
	while (rx < 0) { 
		rx++;	
		cx--;
	}
	while (ry > 1) {
		ry--;	
		cy++; 
	}
	while (ry < 0) {
		ry++;	
		cy--; 
	}

	px = ((cx + rx) * 32);
	py = ((cy + ry) * 32);

	//Collisions

	

	spr.setPosition(px, py);
}

void Character::jump(float y)
{

}

void Character::move(float x, float y)
{
	if (x != 0 && cx > 0 && x < 0)
	dx = x;

	if (x != 0 && cx < 39 && x > 0)
		dx = x;

	if (y != 0 && cy > 0 && y < 0)
	dy = y;

	if (y != 0 && cy < 22 && y > 0)
		dy = y;
}

void Character::setCoordinate(float x, float y)
{
	px = x;
	py = y;
	cx = (px / 32);
	cy = (py / 32);
	rx = (px - cx * 32) / 32;
	ry = (py - cy * 32) / 32;
}

bool Character::hasCollision(float ncx, float ncy)
{
	//check chaque entity


	return false;
}

void Character::collided(Character* wall)
{
	if ((cx - 1 == wall->cx && (cy == wall->cy || cy == wall->cy - 1)) && rx <= 0.2)
	{
		rx += 0.04f;
		dx = 0;
	}
	if ((cx + 1 == wall->cx) && (cy == wall->cy || cy == wall->cy - 1))
	{
		rx -= 0.04f;
		dx = 0;
	}
	if ((cy - 1 == wall->cy && (cx == wall->cx || cx == wall->cx - 1)) && ry <= 0.2)
	{
		ry += 0.04f;
		dy = 0;
	}
	if ((cy + 1 == wall->cy) && (cx == wall->cx || cx == wall->cx - 1))
	{
		ry -= 0.04f;
		dy = 0;
	}
	return;
}

void Character::draw(sf::RenderWindow & win)
{
	win.draw(this->spr);
}
